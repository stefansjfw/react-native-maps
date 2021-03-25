#pragma once

#include "pch.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "RNMapIconModule.g.h"

namespace winrt::RNMaps::implementation
{

    class RNMapIconModule : public RNMapIconModuleT<RNMapIconModule>
    {
    public:
        RNMapIconModule(Microsoft::ReactNative::IReactContext const &reactContext);

        static winrt::Windows::Foundation::Collections::
            IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
            NativeProps() noexcept;
        void UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const &propertyMapReader) noexcept;

        static winrt::Microsoft::ReactNative::ConstantProviderDelegate
        ExportedCustomBubblingEventTypeConstants() noexcept;
        static winrt::Microsoft::ReactNative::ConstantProviderDelegate
        ExportedCustomDirectEventTypeConstants() noexcept;

        static winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> Commands() noexcept;
        void DispatchCommand(
            winrt::hstring const &commandId,
            winrt::Microsoft::ReactNative::IJSValueReader const &commandArgsReader) noexcept;

        void AddToMap(Windows::UI::Xaml::Controls::Maps::MapControl const &map);

    private:
        void UpdateMapIcon();
        Microsoft::ReactNative::IReactContext m_reactContext{nullptr};

        std::string m_title;
        std::string m_description;
        std::string m_imagePath;
        Windows::Devices::Geolocation::BasicGeoposition m_coordinate;
        std::optional<Point> m_anchor;
        std::string m_identifier;
        bool m_draggable{ false };
        Windows::UI::Xaml::Controls::Maps::MapIcon m_mapIcon{};
    };
}

namespace winrt::RNMaps::factory_implementation
{
    struct RNMapIconModule : RNMapIconModuleT<RNMapIconModule, implementation::RNMapIconModule>
    {
    };
}
