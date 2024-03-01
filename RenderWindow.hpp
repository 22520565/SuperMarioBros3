#pragma once
#include "Window.hpp"
#include "RenderTarget.hpp"

namespace game {
	class RenderWindow final : public Window, public RenderTarget {
	private:
	public:
		RenderWindow(const Vector2<int>& size, int nCmdShow)
			: Window(size, nCmdShow), RenderTarget(this->hWnd) {}

		Vector2<int> getSize() const override { return Window::getSize(); }

		void display() { pSwapChain->Present(1, 0); }
	};
}
