#include <stdio.h>
#include <iostream>

#include "NullRenderer.h"

#include <Logging/Logger.h>

#include "../ClientStyle.h"

using namespace Sapphire::GUI;

Renderer::NullRenderer::NullRenderer()
{  

}

Renderer::NullRenderer::~NullRenderer()
{
   
}

void Renderer::NullRenderer::init( ClientControlPtr clientControl )
{
   m_pClientControl = clientControl;
}

void Renderer::NullRenderer::render()
{

}

void Renderer::NullRenderer::dispose()
{

}