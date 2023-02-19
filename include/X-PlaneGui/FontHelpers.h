// Created by Arthur Meeh on 19.02.23.

#pragma once

#include "OpenGL/gl.h"
#include "imgui.h"
#include "XPLMGraphics.h"

namespace XP_GUI {
	static ImFontAtlas* CreateXPFontAtlas()
	{
		// bind default font
		unsigned char* pixels;
		int width, height;

		auto fontAtlas = new ImFontAtlas();
		fontAtlas->GetTexDataAsAlpha8(&pixels, &width, &height);

		// slightly stupid dance around the texture number due to XPLM not using GLint here.
		int texNum = 0;
		XPLMGenerateTextureNumbers(&texNum, 1);

		// upload texture.
		XPLMBindTexture2d(texNum, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);
		fontAtlas->TexID = (void*)(uintptr_t)texNum;

		return fontAtlas;
	}

	static void DestroyFontAtlas(ImFontAtlas* fontAtlas)
	{
		if (fontAtlas == nullptr)
		{
			return;
		}
		auto t = (GLuint)(uintptr_t)fontAtlas->TexID;
		glDeleteTextures(1, &t);
	}
}