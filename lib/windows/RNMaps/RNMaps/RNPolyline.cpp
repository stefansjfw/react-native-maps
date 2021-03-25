#include "pch.h"
#include "JSValueXaml.h"
#include "RNPolyline.h"
#include "RNPolylineModule.g.cpp"

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Data::Json;
    using namespace Windows::Devices::Geolocation;
    using namespace Windows::Foundation;
    using namespace Windows::UI;
    using namespace Windows::UI::Popups;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
    using namespace Windows::UI::Xaml::Controls::Maps;
    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml::Media;
} // namespace winrt

namespace winrt::RNMaps::implementation
{

    RNPolylineModule::RNPolylineModule(winrt::IReactContext const &reactContext) : m_reactContext(reactContext)
    {
    }

    winrt::Windows::Foundation::Collections::
        IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
        RNPolylineModule::NativeProps() noexcept
    {
        // TODO(stefan): cleanup
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
        nativeProps.Insert(L"coordinates", ViewManagerPropertyType::Array);
        nativeProps.Insert(L"tappable", ViewManagerPropertyType::Boolean);
        // not applicable - nativeProps.Insert(L"fillColor", ViewManagerPropertyType::Color);
        nativeProps.Insert(L"strokeWidth", ViewManagerPropertyType::Number);
        nativeProps.Insert(L"strokeColor", ViewManagerPropertyType::Color);
        // not applicable - nativeProps.Insert(L"strokeColors", ViewManagerPropertyType::Array);
        nativeProps.Insert(L"zIndex", ViewManagerPropertyType::Number);
        // not applicable - nativeProps.Insert(L"lineCap", ViewManagerPropertyType::String);
        // not applicable - nativeProps.Insert(L"lineJoin", ViewManagerPropertyType::String);
        // not applicable - nativeProps.Insert(L"miterLimit", ViewManagerPropertyType::Number);
        // not applicable - nativeProps.Insert(L"geodesic", ViewManagerPropertyType::Boolean);
        // not applicable - nativeProps.Insert(L"lineDashPhase", ViewManagerPropertyType::String);
        // partially applicable - dashed - true/false, no custom patterns
        nativeProps.Insert(L"lineDashPattern", ViewManagerPropertyType::Array);
        return nativeProps.GetView();
    }

    void RNPolylineModule::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const &propertyMapReader) noexcept
    {
        const JSValueObject &propertyMap = JSValue::ReadObjectFrom(propertyMapReader);
        for (auto const &pair : propertyMap)
        {
            auto const &propertyName = pair.first;
            auto const &propertyValue = pair.second;
            if (propertyName == "coordinates")
            {
                if (!propertyValue.IsNull())
                {
                    m_coordinates.clear();
                    auto const &positions = propertyValue.AsArray();
                    for (const auto &position : positions)
                    {
                        const auto &lat = position.AsObject()["latitude"].AsDouble();
                        const auto &lon = position.AsObject()["longitude"].AsDouble();
                        m_coordinates.push_back({lat, lon, 111});
                    }
                }
            }
            if (propertyName == "tappable")
            {
                if (!propertyValue.IsNull())
                {
                    const auto &tappable = propertyValue.AsBoolean();
                    m_tappable = tappable;
                }
                else
                {
                    m_tappable = false;
                }
            }
            if (propertyName == "strokeWidth")
            {
                if (!propertyValue.IsNull())
                {
                    const auto &strokeWidth = propertyValue.AsDouble();
                    m_strokeWidth = strokeWidth;
                }
                else
                {
                    m_strokeWidth = 1;
                }
            }
            if (propertyName == "strokeColor")
            {
                if (!propertyValue.IsNull())
                {
                    m_strokeColor = propertyValue.To<Color>(Colors::Black());
                }
                else
                {
                    m_strokeColor = Colors::Black();
                }
            }
            if (propertyName == "zIndex")
            {
                if (!propertyValue.IsNull())
                {
                    const auto &zIndex = propertyValue.AsUInt8();
                    m_zIndex = zIndex;
                }
                else
                {
                    m_zIndex = 0;
                }
            }
            if (propertyName == "lineDashPattern")
            {
                if (!propertyValue.IsNull())
                {
                    m_strokeDashed = true;
                }
                else
                {
                    m_strokeDashed = false;
                }
            }
        }
        UpdatePolyline();
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNPolylineModule::ExportedCustomBubblingEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNPolylineModule::ExportedCustomDirectEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> RNPolylineModule::Commands() noexcept
    {
        // TODO: deifne commands supported by the control
        auto commands = winrt::single_threaded_vector<hstring>();
        commands.Append(L"sampleCommand");
        return commands.GetView();
    }

    void RNPolylineModule::DispatchCommand(winrt::hstring const &commandId, winrt::Microsoft::ReactNative::IJSValueReader const &commandArgsReader) noexcept
    {
        // TODO: handle commands here
    }

    void RNPolylineModule::AddToMap(MapControl const &map)
    {
        if (m_coordinates.size() > 0)
        {
            UpdatePolyline();

            map.MapElements().Append(m_polyline);
        }
    }

    void RNPolylineModule::UpdatePolyline()
    {
        m_polyline.IsEnabled(m_tappable);
        m_polyline.Path(Windows::Devices::Geolocation::Geopath(m_coordinates));
        m_polyline.ZIndex(m_zIndex);
        m_polyline.StrokeThickness(m_strokeWidth);
        m_polyline.StrokeDashed(m_strokeDashed);
        m_polyline.StrokeColor(m_strokeColor);
    }
}