#pragma once
#include <atlcomcli.h>
#include <d3d10.h>
namespace game {
    class DxResource {
    public:
        const CComPtr<ID3D10Device>*const pD3DDevice = nullptr;

        constexpr explicit DxResource(const CComPtr<ID3D10Device>* const device) noexcept : pD3DDevice(device) {}

        constexpr ~DxResource() noexcept = default;

    private:

        constexpr DxResource(const DxResource&) noexcept = delete;
        constexpr DxResource(DxResource&&) noexcept = delete;
        constexpr DxResource& operator=(const DxResource&) noexcept = delete;
        constexpr DxResource& operator=(DxResource&&) noexcept = delete;
    };
}
