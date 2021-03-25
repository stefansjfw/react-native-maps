#pragma once

#include "pch.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "RNPolylineModule.g.h"

namespace winrt::RNMaps::implementation
{

    class RNPolylineModule : public RNPolylineModuleT<RNPolylineModule>
    {
    public:
        RNPolylineModule(Microsoft::ReactNative::IReactContext const &reactContext);

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
        void UpdatePolyline();
        Microsoft::ReactNative::IReactContext m_reactContext{nullptr};

        std::vector<Windows::Devices::Geolocation::BasicGeoposition> m_coordinates;
        bool m_tappable{false};
        double m_strokeWidth{1};
        Windows::UI::Color m_strokeColor{Windows::UI::Colors::Black()};
        int m_zIndex{0};
        bool m_strokeDashed{false};
        Windows::UI::Xaml::Controls::Maps::MapPolyline m_polyline{};
    };
}

namespace winrt::RNMaps::factory_implementation
{
    struct RNPolylineModule : RNPolylineModuleT<RNPolylineModule, implementation::RNPolylineModule>
    {
    };
}
