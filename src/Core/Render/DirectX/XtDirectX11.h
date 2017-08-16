#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
namespace render {
	class XtDirectX11 : public IXtRenderDevice {
	public:
		XtDirectX11(int width, int height, bool fullscreen = false) : IXtRenderDevice(width, height, fullscreen) {}
		~XtDirectX11() override;

		bool init() override;
		void changeViewport(int width, int height) override;
		void drawFrame(float delta) override;
	};
}
}