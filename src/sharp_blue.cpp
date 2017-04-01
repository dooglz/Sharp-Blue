#include "sharp_blue.h"
#include "GL/glew.h"
#include "SDL.h"
#include "concurrency.h"
#include <atomic>
#include <chrono>
#include <iostream>

#include <thread>
using namespace std;


namespace sb {
unsigned int currentTick;
unsigned int currentFrame;
SDL_Window *window;
atomic<bool> gotime(false);
thread t_runner_1, t_runner_2;

void TaskRunner();

void Task_EndFrame(void *arg);
void MTask_PollEvents(void *arg);
void MTask_Render(void *arg);
void Task_GameLogic(void *arg);

bool CheckGL() {
  GLenum err;
  bool ret = false;
  while ((err = glGetError()) != GL_NO_ERROR) {
    printf("\n A general OGL error has occured: %i\n", err);
    ret = true;
  }
  return ret;
}

void DebugCallbackAMD(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar *message,
                      GLvoid *userParam) {
  printf("\nAn OGL AMD error has occured: %s\n", message);
}

void DebugCallbackARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                      GLvoid *userParam) {
  printf("\nAn OGL ARB error has occured: %s\n", message);
}

void printOutKhrDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                             const GLchar *message, const void *userParam) {
  printf("\nAn OGL KHR error has occured: %s\n", message);
}

static void GlewInfo() {
  printf("----------------------OpenGL Info----------------------------\n");
  printf("Glew Version: %s\n", glewGetString(GLEW_VERSION));
  printf("     Version: %s\n", glGetString(GL_VERSION));
  printf("      Vendor: %s\n", glGetString(GL_VENDOR));
  printf("    Renderer: %s\n", glGetString(GL_RENDERER));
  printf("     Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  printf("-------------------------------------------------------------\n");
}

void version() { cout << "Sharp Blue Version 1" << endl; }


bool init() {
  SDL_assert(SDL_Init(SDL_INIT_VIDEO) >= 0);

  window = SDL_CreateWindow("Sharp Blue", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  SDL_assert(window != NULL);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
  //-------------------------------------------------------------------
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Create context
  SDL_GLContext gContext = SDL_GL_CreateContext(window);
  SDL_assert(gContext != NULL);
  CheckGL();

  // init Glew
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    return false;
  }
  glGetError(); // Experimental init throws junk errors, Ignore.

  GlewInfo();
  if (GLEW_ARB_debug_output) {
    printf("Supporting Arb output\n");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallbackARB((GLDEBUGPROCARB)DebugCallbackARB, 0);
    CheckGL();
  }

  if (GLEW_AMD_debug_output) {
    printf("Supporting AMD output\n");
    glDebugMessageCallbackAMD((GLDEBUGPROCAMD)DebugCallbackAMD, 0);
    CheckGL();
  }

  if (GLEW_KHR_debug) {
    printf("Supporting KHR output\n");
    glDebugMessageCallback((GLDEBUGPROC)printOutKhrDebugMessage, 0);
    CheckGL();
  }

  if (CheckGL()) {
    return false;
  }

  return true;
}

void OnEvent(SDL_Event *Event) {}

void MTask_PollEvents(void *arg) {
  SDL_Event Event;
  while (SDL_PollEvent(&Event) != 0) {
    OnEvent(&Event);
    if (Event.type == SDL_QUIT)
      gotime = false;
  }
  cout << "poll" << endl;
}

void Task_EndFrame(void *arg) {
  auto poll = cc::AddTask(0, cc::makeTask(MTask_PollEvents));
  auto logic = cc::AddTask(1, cc::makeTask(Task_GameLogic,{poll}));
  cc::AddTask(0, cc::makeTask(MTask_Render,{poll,logic}));
   cout << "End" << endl;
}

void MTask_Render(void *arg) {
  SDL_GL_SetSwapInterval(1);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
  CheckGL();
  cc::AddTask(1, cc::makeTask(Task_EndFrame));
   cout << "Render" << endl;
}

void Task_GameLogic(void *arg) {
  this_thread::sleep_for(chrono::milliseconds(5));
   cout << "GameLogic" << endl;
}

void Start() {
  currentTick = 0;
  currentFrame = 0;
  gotime = true;
  t_runner_1 = thread(TaskRunner);
  t_runner_2 = thread(TaskRunner);

  cc::AddTask(1, cc::makeTask(Task_EndFrame));
  shared_ptr<cc::Task> t;
  while (gotime) {
    t = cc::GetTask(0);
    if (t == NULL) {
      this_thread::sleep_for(chrono::milliseconds(1));
    } else {
      t->tf(nullptr);
    }
  }
  t_runner_1.join();
  t_runner_2.join();
}

void TaskRunner() {
  shared_ptr<cc::Task> t;
  while (gotime) {
    t = cc::GetTask(1);
    if (t == NULL) {
      this_thread::sleep_for(chrono::milliseconds(1));
    } else {
      t->tf(nullptr);
    }
  }
}
}