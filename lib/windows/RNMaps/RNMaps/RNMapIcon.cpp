#include "pch.h"
#include "JSValueXaml.h"
#include "RNMapIcon.h"
#include "RNMapIconModule.g.cpp"

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Data::Json;
    using namespace Windows::Devices::Geolocation;
    using namespace Windows::Foundation;
    using namespace Windows::Storage::Streams;
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

    RNMapIconModule::RNMapIconModule(winrt::IReactContext const &reactContext) : m_reactContext(reactContext)
    {
    }

    winrt::Windows::Foundation::Collections::
        IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
        RNMapIconModule::NativeProps() noexcept
    {
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
        nativeProps.Insert(L"title", ViewManagerPropertyType::String);
        nativeProps.Insert(L"description", ViewManagerPropertyType::String);
        nativeProps.Insert(L"image", ViewManagerPropertyType::String);
        // not applicable - nativeProps.Insert(L"icon", ViewManagerPropertyType::String);
        // not applicable - nativeProps.Insert(L"pinColor", ViewManagerPropertyType::String);
        nativeProps.Insert(L"coordinate", ViewManagerPropertyType::Map);
        //nativeProps.Insert(L"centerOffset", ViewManagerPropertyType::Map);
        //nativeProps.Insert(L"calloutOffset", ViewManagerPropertyType::Map);
        nativeProps.Insert(L"anchor", ViewManagerPropertyType::Map);
        nativeProps.Insert(L"calloutAnchor", ViewManagerPropertyType::Map);
        //nativeProps.Insert(L"flat", ViewManagerPropertyType::Boolean);
        nativeProps.Insert(L"identifier", ViewManagerPropertyType::String);
        //nativeProps.Insert(L"rotation", ViewManagerPropertyType::Number);
        nativeProps.Insert(L"draggable", ViewManagerPropertyType::Boolean);
        //nativeProps.Insert(L"tracksViewChanges", ViewManagerPropertyType::Boolean);
        //nativeProps.Insert(L"tracksInfoWindowChanges", ViewManagerPropertyType::Boolean);
        //nativeProps.Insert(L"stopPropagation", ViewManagerPropertyType::Boolean);
        //nativeProps.Insert(L"opacity", ViewManagerPropertyType::Number);
        //nativeProps.Insert(L"isPreselected", ViewManagerPropertyType::Boolean);
        //nativeProps.Insert(L"key", ViewManagerPropertyType::String);
        return nativeProps.GetView();
    }

    void RNMapIconModule::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const &propertyMapReader) noexcept
    {
        const JSValueObject &propertyMap = JSValue::ReadObjectFrom(propertyMapReader);
        for (auto const &pair : propertyMap)
        {
            auto const &propertyName = pair.first;
            auto const &propertyValue = pair.second;
            if (propertyName == "title")
            {
              if (!propertyValue.IsNull())
              {
                auto const& title = propertyValue.AsString();
                m_title = title;
              }
              else {
                m_title.clear();
              }
            }
            if (propertyName == "description")
            {
              if (!propertyValue.IsNull())
              {
                auto const& description = propertyValue.AsString();
                m_description = description;
              }
              else {
                m_description.clear();
              }
            }
            if (propertyName == "image")
            {
              if (!propertyValue.IsNull())
              {
                auto const& imagePath = propertyValue.AsString();
                m_imagePath = imagePath;
              }
              else {
                m_imagePath.clear();
              }
            }
            if (propertyName == "coordinate")
            {
              if (!propertyValue.IsNull())
              {
                auto const& coordinate = propertyValue.AsObject();
                const auto& lat = coordinate["latitude"].AsDouble();
                const auto& lon = coordinate["longitude"].AsDouble();
                m_coordinate = { lat, lon, 0 };
              }
            }
            if (propertyName == "anchor")
            {
              if (!propertyValue.IsNull())
              {
                auto const& anchorPoint = propertyValue.AsObject();
                const auto& x = anchorPoint["x"].AsSingle();
                const auto& y = anchorPoint["y"].AsSingle();
                m_anchor = { x, y };
              }
              else {
                m_anchor.reset();
              }
            }
            if (propertyName == "identifier")
            {
              if (!propertyValue.IsNull())
              {
                auto const& identifier = propertyValue.AsString();
                m_identifier = identifier;
              }
              else {
                m_identifier.clear();
              }
            }
            if (propertyName == "dragable")
            {
              if (!propertyValue.IsNull())
              {
                m_draggable = true;
              }
            }
        }
        UpdateMapIcon();
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNMapIconModule::ExportedCustomBubblingEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNMapIconModule::ExportedCustomDirectEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> RNMapIconModule::Commands() noexcept
    {
        // TODO: deifne commands supported by the control
        auto commands = winrt::single_threaded_vector<hstring>();
        commands.Append(L"sampleCommand");
        return commands.GetView();
    }

    void RNMapIconModule::DispatchCommand(winrt::hstring const &commandId, winrt::Microsoft::ReactNative::IJSValueReader const &commandArgsReader) noexcept
    {
        // TODO: handle commands here
    }

    void RNMapIconModule::AddToMap(MapControl const &map)
    {
      UpdateMapIcon();
      map.MapElements().Append(m_mapIcon);
    }

    void RNMapIconModule::UpdateMapIcon()
    {
      m_mapIcon.Location(Geopoint(m_coordinate));

      std::string title{ m_title };
      if (!m_description.empty()) {
        title += '\n' + m_description;
      }
      m_mapIcon.Title(to_hstring(title));
      if (!m_imagePath.empty()) {
        Uri uri{ to_hstring(m_imagePath) };
        RandomAccessStreamReference mapIconStreamRef = RandomAccessStreamReference::CreateFromUri(uri);
        m_mapIcon.Image(mapIconStreamRef);
      }
      if (m_anchor.has_value()) {
        m_mapIcon.NormalizedAnchorPoint(*m_anchor);
      }
    }
}