#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
namespace render {
	class XtDirectX11 : public IXtRenderDevice {
	public:
		XtDirectX11(int width, int height, bool fullscreen = false, bool vsync = false) : 
			IXtRenderDevice(width, height, fullscreen), 
			//Self
			_renderUseVSYNC(vsync),
			_renderDevice(nullptr),
			_renderDeviceSwapChain(nullptr),
			_renderDeviceContext(nullptr),
			_renderTargetView(nullptr),
			_renderStencilBuffer(nullptr),
			_renderStencilState(nullptr),
			_renderStencilView(nullptr),
			_renderRasterState(nullptr) {}
		
		~XtDirectX11() override;

		bool init() override;
		void changeViewport(int width, int height) override;
		void drawFrame(float delta) override;
	private:
		bool						_renderUseVSYNC;

		ID3D11Device*				_renderDevice;
		IDXGISwapChain*				_renderDeviceSwapChain;
		ID3D11DeviceContext*		_renderDeviceContext;
		ID3D11RenderTargetView*		_renderTargetView;
		ID3D11Texture2D*			_renderStencilBuffer;
		ID3D11DepthStencilState*	_renderStencilState;
		ID3D11DepthStencilView*		_renderStencilView;
		ID3D11RasterizerState*		_renderRasterState;

		D3DXMATRIX					_renderProjectionMatrix;
		D3DXMATRIX					_renderWorldMatrix;
		D3DXMATRIX					_renderOrthoMatrix;
	};
}
}