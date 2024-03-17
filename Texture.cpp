#include "Texture.hpp"

namespace game {
    bool Texture::loadFromFile(const TCHAR *const &fileName) noexcept {
        bool fileLoaded = false;

        // Retrieve image information first
        D3DX10_IMAGE_INFO imageInfo;
        if (HRESULT hr = D3DX10GetImageInfoFromFile(fileName, nullptr, &imageInfo, nullptr);
            FAILED(hr)) {
            DebugOut(L"[ERROR] D3DX10GetImageInfoFromFile failed for file: %s with error: %d\n", fileName, hr);
        } else {
            this->texture = nullptr;
            D3DX10_IMAGE_LOAD_INFO info = D3DX10_IMAGE_LOAD_INFO();
            info.Width = imageInfo.Width;
            info.Height = imageInfo.Height;
            info.Depth = imageInfo.Depth;
            info.FirstMipLevel = 0;
            info.MipLevels = 1;
            info.Usage = D3D10_USAGE_DEFAULT;
            info.Format = imageInfo.Format;
            info.Filter = D3DX10_FILTER_NONE;
            info.pSrcInfo = &imageInfo;

            CComPtr<ID3D10Resource> pD3D10Resource = CComPtr<ID3D10Resource>();
            // Loads the texture into a temporary ID3D10Resource object
            if (hr = D3DX10CreateTextureFromFile(*this->pD3DDevice, fileName, &info,
                                                 nullptr, &pD3D10Resource, nullptr);
                FAILED(hr)) { // Make sure the texture was loaded successfully
                DebugOut(L"[ERROR] Failed to load texture file: %s with error: %d\n", fileName, hr);
            } else {
                // Translates the ID3D10Resource object into a ID3D10Texture2D object
                pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID *)&this->texture);

                if (this->texture == nullptr) {
                    DebugOut(L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
                } else {
                    //
                    // Create the Share Resource View for this texture
                    //
                    // Get the texture details
                    D3D10_TEXTURE2D_DESC desc;
                    this->texture->GetDesc(&desc);
                    this->size.x = desc.Width;
                    this->size.y = desc.Height;

                    // Create a shader resource view of the texture
                    const D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc = D3D10_SHADER_RESOURCE_VIEW_DESC{
                        // Set the texture format
                        .Format = desc.Format,
                        // Set the type of resource
                        .ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D,
                        .Texture2D = D3D10_TEX2D_SRV{
                            .MostDetailedMip = UINT(),
                            .MipLevels = desc.MipLevels,
                        },
                    };
                    // TODO: shall we remove this?
                    this->shaderResourceView = nullptr;
                    if (hr = (*this->pD3DDevice)->CreateShaderResourceView(this->texture, &SRVDesc, &this->shaderResourceView);
                        FAILED(hr)) {
                    } else {
                        DebugOut(L"[INFO] Texture loaded Ok from file: %s \n", fileName);
                        fileLoaded = true;
                    }
                }
            }
        }
        return fileLoaded;
    }
}
