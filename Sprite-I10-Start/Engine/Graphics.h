/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Surface.h"
#include "Rect.h"
#include "assert.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	Color GetPixel(int x, int y) const;

	template<typename E>
	void DrawSprite(int x, int y, const Surface& s, E effect)
	{
		DrawSprite(x, y, s.GetRect(), s, effect);
	}

	template<typename E>
	void DrawSprite(int x, int y, const RectI& rect, const Surface& s, E effect)
	{
		DrawSprite(x, y, rect, Graphics::GetScreenRect(), s, effect);
	}

	// x y is where the region of the section of the sprite will go on the screen
	// rect specifies that region within the sprite. and Surface is the sprite itself.
	template<typename E>
	void DrawSprite(int x, int y, RectI rect, const RectI& clip, const Surface& s, E effect)
	{
		// ensure rect is within the surface
		assert(rect.left >= 0);
		assert(rect.top >= 0);
		assert(rect.right <= s.GetWidth());
		assert(rect.bottom <= s.GetHeight());

		if (x < clip.left)
		{
			rect.left += clip.left - x;
			x = clip.left;
		}

		if (y < clip.top)
		{
			rect.top += clip.top - y;
			y = clip.top;
		}

		if (x + rect.GetWidth() > clip.right)
		{
			rect.right = rect.right - (x + rect.GetWidth() - clip.right);
		}

		if (y + rect.GetHeight() > clip.bottom)
		{
			rect.bottom = rect.bottom - (y + rect.GetHeight() - clip.bottom);
		}

		for (int sx{ rect.left }; sx < rect.right; ++sx)
		{
			for (int sy{ rect.top }; sy < rect.bottom; ++sy)
			{
				const int x_final = x + sx - rect.left;
				const int y_final = y + sy - rect.top;
				effect(s.GetPixel(sx, sy), x_final, y_final, *this);
			}
		}
	}

	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
	static RectI GetScreenRect();
};