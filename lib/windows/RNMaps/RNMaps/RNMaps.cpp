#include "pch.h"
#include "JSValueXaml.h"
#include "RNMaps.h"
#include "RNMapsModule.g.cpp"

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Data::Json;
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

    RNMapsModule::RNMapsModule(winrt::IReactContext const &reactContext) : m_reactContext(reactContext)
    {
        m_mapControl = Windows::UI::Xaml::Controls::Maps::MapControl();
        m_mapControl.MapServiceToken(to_hstring("KA7ok2YJyQvS2SsCVE9w~LD0jXhKIql415PaY9guzCA~AnjWdcuulxsf2een-Ri99yabvNkpH1XX7HjvxhjD1JsluQ_e0zuiBE62KUpoTpg-"));
        this->Children().Append(m_mapControl);
        mTextBlock = TextBlock();
        mTextBlock.Text(to_hstring("This text demonstrates the wrapping behavior of a TextBlock."));
        this->Children().Append(mTextBlock);
    }

    winrt::Windows::Foundation::Collections::
        IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
        RNMapsModule::NativeProps() noexcept
    {
        // TODO: define props here
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
        nativeProps.Insert(L"sampleProp", ViewManagerPropertyType::String);
        return nativeProps.GetView();
    }

    void RNMapsModule::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const &propertyMapReader) noexcept
    {
        mText = mText + to_hstring("aaa ");
        mTextBlock.Text(mText);
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNMapsModule::ExportedCustomBubblingEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNMapsModule::ExportedCustomDirectEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> RNMapsModule::Commands() noexcept
    {
        // TODO: deifne commands supported by the control
        auto commands = winrt::single_threaded_vector<hstring>();
        commands.Append(L"sampleCommand");
        return commands.GetView();
    }

    void RNMapsModule::DispatchCommand(winrt::hstring const &commandId, winrt::Microsoft::ReactNative::IJSValueReader const &commandArgsReader) noexcept
    {
        // TODO: handle commands here
    }

    void RNMapsModule::AddFeature(winrt::Windows::UI::Xaml::UIElement child, int64_t index) {
        m_features.insert({ index, child });
        if (auto childModule = child.try_as<winrt::RNMaps::RNPolylineModule>()) {
            childModule.AddToMap(m_mapControl);
        }
        else if (auto childModule = child.try_as<winrt::RNMaps::RNMapIconModule>()) {
            childModule.AddToMap(m_mapControl);
        }
    }
}