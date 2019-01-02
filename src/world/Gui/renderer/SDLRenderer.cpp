#include <stdio.h>
#include <iostream>

#include "SDLRenderer.h"

#include <Logging/Logger.h>
#include <Version.h>

#include "../ClientStyle.h"
#include "../window/WindowManager.h"

using namespace Sapphire::GUI;

Renderer::SDLRenderer::SDLRenderer()
{

}

Renderer::SDLRenderer::~SDLRenderer()
{
   Logger::error( "Renderer destroyed" );
}

void Renderer::SDLRenderer::init( ClientControlPtr clientControl )
{
  std::string windowTitle = "Sapphire - " + Version::VERSION + "[" + Version::GIT_HASH + "]";

   m_pClientControl = clientControl;

   Logger::info( "Using SDL Renderer" );
   if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 )
   {
      Logger::error( SDL_GetError() );
      return;
   }

   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
   SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
   SDL_DisplayMode current;
   SDL_GetCurrentDisplayMode( 0, &current );
   m_pSDLWindow = SDL_CreateWindow( windowTitle.c_str(), 
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
      m_pClientControl->clientWidth, m_pClientControl->clientHeight,
      SDL_WINDOW_OPENGL );

   m_SDLGLContext = SDL_GL_CreateContext( m_pSDLWindow );
   SDL_GL_SetSwapInterval( 1 ); // Enable vsync

   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   m_ImGuiIO = ImGui::GetIO(); ( void )m_ImGuiIO;
   //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

   Logger::info( "SDL init successful" );
   Logger::info( "Creating OpenGL context" );

   ImGui_ImplSDL2_InitForOpenGL( m_pSDLWindow, m_SDLGLContext );
   ImGui_ImplOpenGL2_Init();

   Logger::info( "OpenGL context created" );

   // Setup style
   Style::applyAppStyle();
   Style::addFont( "mplus-1c-regular.ttf", 18, 36, m_fontData );

   m_background = Style::COLOR_APPBG;
}

void Renderer::SDLRenderer::render()
{
   internalDraw();
}

void Renderer::SDLRenderer::internalDraw()
{
   SDL_Event event;
   while( SDL_PollEvent( &event ) )
   {
      ImGui_ImplSDL2_ProcessEvent( &event );
      if( event.type == SDL_QUIT )
         m_pClientControl->isRunning = false;
   }

   // imgui framing
   ImGui_ImplOpenGL2_NewFrame();
   ImGui_ImplSDL2_NewFrame( m_pSDLWindow );
   ImGui::NewFrame();

   ImGui::ShowDemoWindow();

   m_pClientControl->windowManager.updateWindows();

   // Rendering
   ImGui::Render();
   //glViewport( 0, 0, ( int )io.DisplaySize.x, ( int )io.DisplaySize.y );
   glClearColor( m_background.x, m_background.y, m_background.z, m_background.w );
   glClear( GL_COLOR_BUFFER_BIT );
   //glUseProgram(0);
   ImGui_ImplOpenGL2_RenderDrawData( ImGui::GetDrawData() );
   SDL_GL_SwapWindow( m_pSDLWindow );
}

void Renderer::SDLRenderer::dispose()
{
   Logger::info( "Shutting down renderer" );

   ImGui_ImplOpenGL2_Shutdown();
   ImGui_ImplSDL2_Shutdown();
   ImGui::DestroyContext();

   SDL_GL_DeleteContext( m_SDLGLContext );
   SDL_Quit();
}
