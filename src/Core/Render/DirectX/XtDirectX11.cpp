#include "XtDirectX11.h"

#define DX_ASSERT(resPtr, message) \
	if (FAILED(resPtr)) { \
		LOGMSG("DX ERROR: %s", message); \
		return false;	\
	}

#define XT_SCREEN_NEAR  0.1f
#define XT_SCREEN_DEPTH 10.f

#include <Core/XtEngine.h>

namespace xt {
namespace render {
	XtDirectX11::~XtDirectX11() {
		if (_renderDeviceSwapChain) {
			_renderDeviceSwapChain->SetFullscreenState(0, nullptr);
		}

		if (_renderRasterState) {
			_renderRasterState->Release();
			_renderRasterState = nullptr;
		}

		if (_renderStencilView) {
			_renderStencilView->Release();
			_renderStencilView = nullptr;
		}

		if (_renderStencilState) {
			_renderStencilState->Release();
			_renderStencilState = nullptr;
		}

		if (_renderStencilBuffer) {
			_renderStencilBuffer->Release();
			_renderStencilBuffer = nullptr;
		}

		if (_renderTargetView) {
			_renderTargetView->Release();
			_renderTargetView = nullptr;
		}

		if (_renderDeviceContext) {
			_renderDeviceContext->Release();
			_renderDeviceContext = nullptr;
		}

		if (_renderDevice) {
			_renderDevice->Release();
			_renderDevice = nullptr;
		}

		if (_renderDeviceSwapChain) {
			_renderDeviceSwapChain->Release();
			_renderDeviceSwapChain = nullptr;
		}
	}

	bool XtDirectX11::init() {
		using namespace xt::platform;

		HRESULT		 result							 = 0;
		unsigned int renderAvailableModes			 = 0;
		int deviceNumenator							 = -1;
		int deviceDenominator						 = -1;
		const float fov								 = static_cast<float>(D3DX_PI / 4.0f);
		const float screenAspect					 = static_cast<float>(_width / _height);
		
		IDXGIFactory* renderFactory					 = nullptr;
		IDXGIAdapter* renderAvailableAdapters		 = nullptr;
		IDXGIOutput*  renderAvailableOutputAdapters	 = nullptr;
		DXGI_MODE_DESC* renderDisplayModesList		 = nullptr;

		DXGI_SWAP_CHAIN_DESC renderSwapChainDesc;
		D3D_FEATURE_LEVEL	 renderFeatureLevel		 = D3D_FEATURE_LEVEL_11_0;
		ID3D11Texture2D*	 renderBackBuffer		 = nullptr;
		XtDefaultDevice*	 currentDevice			 = static_cast<XtDefaultDevice*>(xt::XtEngine::getInstance()->getCurrentPlatform());

		D3D11_TEXTURE2D_DESC			depthBufferDesc;
		D3D11_DEPTH_STENCIL_DESC		depthStencilDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC	depthStencilViewDesc;
		D3D11_RASTERIZER_DESC			rasterDesc;

		//RENDER MODES

		result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&renderFactory);
		DX_ASSERT(result, "CreateDXGIFactory failed");
		
		result = renderFactory->EnumAdapters(0, &renderAvailableAdapters);
		DX_ASSERT(result, "EnumAdapters failed");

		result = renderAvailableAdapters->EnumOutputs(0, &renderAvailableOutputAdapters);
		DX_ASSERT(result, "EnumOutputs failed");

		result = renderAvailableOutputAdapters->GetDisplayModeList(
			DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, 
			&renderAvailableModes, 
			nullptr);
		DX_ASSERT(result, "GetDisplayModeList failed");

		renderDisplayModesList = new DXGI_MODE_DESC[renderAvailableModes];
		result = renderAvailableOutputAdapters->GetDisplayModeList(
			DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, 
			&renderAvailableModes, 
			renderDisplayModesList);
		DX_ASSERT(result, "GetDisplayModeList(2) failed");

		if (_renderUseVSYNC) {
			for (unsigned int i = 0; i < renderAvailableModes; i++) {
				if (renderDisplayModesList[i].Width == _width && renderDisplayModesList[i].Height == _height) {
					deviceNumenator = renderDisplayModesList[i].RefreshRate.Numerator;
					deviceDenominator = renderDisplayModesList[i].RefreshRate.Denominator;
				}
			}
		}
		else {
			deviceNumenator = 0;
			deviceDenominator = 1;
		}

		delete[] renderDisplayModesList;
		renderAvailableOutputAdapters->Release();
		renderAvailableAdapters->Release();
		renderFactory->Release();

		//INIT RENDER
		ZeroMemory(&renderSwapChainDesc, sizeof(renderSwapChainDesc));
		renderSwapChainDesc.BufferCount		  = 1;
		renderSwapChainDesc.BufferDesc.Width  = _width;
		renderSwapChainDesc.BufferDesc.Height = _height;
		renderSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		renderSwapChainDesc.BufferDesc.RefreshRate.Numerator = deviceNumenator;
		renderSwapChainDesc.BufferDesc.RefreshRate.Denominator = deviceDenominator;
		renderSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		renderSwapChainDesc.OutputWindow = currentDevice->getCurrentWindow()->getHandle();
		renderSwapChainDesc.SampleDesc.Count = 1;
		renderSwapChainDesc.SampleDesc.Quality = 0;
		renderSwapChainDesc.Windowed = !_fullscreen;
		renderSwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		renderSwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		renderSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		renderSwapChainDesc.Flags = 0;

		result = D3D11CreateDeviceAndSwapChain(
			nullptr, 
			D3D_DRIVER_TYPE_HARDWARE, 
			nullptr, 
			0, 
			&renderFeatureLevel, 
			1,
			D3D11_SDK_VERSION, 
			&renderSwapChainDesc, 
			&_renderDeviceSwapChain, 
			&_renderDevice, 
			nullptr, 
			&_renderDeviceContext);
		DX_ASSERT(result, "D3D11CreateDeviceAndSwapChain failed");

		result = _renderDeviceSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderBackBuffer);
		DX_ASSERT(result, "GetBuffer for _renderDeviceSwapChain failed");

		result = _renderDevice->CreateRenderTargetView(renderBackBuffer, NULL, &_renderTargetView);
		DX_ASSERT(result, "CreateRenderTargetView for _renderDevice failed");
		renderBackBuffer->Release();

		//DEPTH BUFFER
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		// Set up the description of the depth buffer.
		depthBufferDesc.Width				= _width;
		depthBufferDesc.Height				= _height;
		depthBufferDesc.MipLevels			= 1;
		depthBufferDesc.ArraySize			= 1;
		depthBufferDesc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count	= 1;
		depthBufferDesc.SampleDesc.Quality	= 0;
		depthBufferDesc.Usage				= D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags		= 0;
		depthBufferDesc.MiscFlags			= 0;

		result = _renderDevice->CreateTexture2D(&depthBufferDesc, NULL, &_renderStencilBuffer);
		DX_ASSERT(result, "CreateTexture2D for _renderDevice failed");

		//STENCIL STATE
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		depthStencilDesc.DepthEnable					= true;
		depthStencilDesc.DepthWriteMask					= D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc						= D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable					= true;
		depthStencilDesc.StencilReadMask				= 0xFF;
		depthStencilDesc.StencilWriteMask				= 0xFF;

		depthStencilDesc.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;

		depthStencilDesc.BackFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp	= D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;

		result = _renderDevice->CreateDepthStencilState(&depthStencilDesc, &_renderStencilState);
		DX_ASSERT(result, "CreateDepthStencilState for _renderDevice failed");

		_renderDeviceContext->OMSetDepthStencilState(_renderStencilState, 1);

		//STENCIL VIEW
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		// Set up the depth stencil view description.
		depthStencilViewDesc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension		= D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		result = _renderDevice->CreateDepthStencilView(_renderStencilBuffer, &depthStencilViewDesc, &_renderStencilView);
		DX_ASSERT(result, "CreateDepthStencilView for _renderDevice failed");

		_renderDeviceContext->OMSetRenderTargets(1, &_renderTargetView, _renderStencilView);

		//RASTER
		/**
		 * @note: нужно пересмотреть в будущем это место, пока оставлю так
		 */
		rasterDesc.AntialiasedLineEnable	= true;
		rasterDesc.CullMode					= D3D11_CULL_BACK;
		rasterDesc.DepthBias				= 0;
		rasterDesc.DepthBiasClamp			= 0.0f;
		rasterDesc.DepthClipEnable			= true;
		rasterDesc.FillMode					= D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise	= false;
		rasterDesc.MultisampleEnable		= false;
		rasterDesc.ScissorEnable			= false;
		rasterDesc.SlopeScaledDepthBias		= 0.0f;

		result = _renderDevice->CreateRasterizerState(&rasterDesc, &_renderRasterState);
		DX_ASSERT(result, "CreateRasterizerState failed");

		_renderDeviceContext->RSSetState(_renderRasterState);

		//VIEWPORT
		D3D11_VIEWPORT					viewport;

		viewport.Width    = static_cast<float>(_width);
		viewport.Height   = static_cast<float>(_height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		_renderDeviceContext->RSSetViewports(1, &viewport);

		//FIELD OF VIEW
		D3DXMatrixPerspectiveFovLH(&_renderProjectionMatrix, fov, screenAspect, XT_SCREEN_NEAR, XT_SCREEN_DEPTH);
		D3DXMatrixIdentity(&_renderWorldMatrix);
		D3DXMatrixOrthoLH(&_renderOrthoMatrix, static_cast<float>(_width), static_cast<float>(_height), XT_SCREEN_NEAR, XT_SCREEN_DEPTH);

		return true;
	}

	void XtDirectX11::changeViewport(int width, int height) {

	}

	void XtDirectX11::drawFrame(float delta) {
		//BEGIN
		const float backBufferColor[4] = { 0.f, 0.f, 1.f, 1.f };
		_renderDeviceContext->ClearRenderTargetView(_renderTargetView,  backBufferColor);
		_renderDeviceContext->ClearDepthStencilView(_renderStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		//RENDER
		//TODO: Render all
		//END
		_renderDeviceSwapChain->Present((_renderUseVSYNC ? 1 : 0), 0);
	}
}
}