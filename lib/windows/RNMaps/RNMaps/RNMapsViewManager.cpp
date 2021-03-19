#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "RNMapsViewManager.h"
#include "RNMaps.h"

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
    using namespace Windows::UI;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
}

namespace winrt::RNMaps::implementation
{
    // IViewManager
    winrt::hstring RNMapsViewManager::Name() noexcept
    {
        return L"RNMapsWindowsTest";
    }

    winrt::FrameworkElement RNMapsViewManager::CreateView() noexcept
    {
        return winrt::RNMaps::RNMapsModule(m_reactContext);
    }

    // IViewManagerWithChildren
    void RNMapsViewManager::AddView(FrameworkElement parent, UIElement child, int64_t index)
    {
        if (auto module = parent.try_as<winrt::RNMaps::RNMapsModule>())
        {
            module.UpdateProperties(nullptr);
            module.UpdateProperties(nullptr);
            module.UpdateProperties(nullptr);
        }
    }

    void RNMapsViewManager::RemoveAllChildren(FrameworkElement parent) {}
    void RNMapsViewManager::RemoveChildAt(FrameworkElement parent, int64_t index) {}
    void RNMapsViewManager::ReplaceChild(FrameworkElement parent, UIElement oldChild, UIElement newChild) {}

    // IViewManagerWithReactContext
    winrt::IReactContext RNMapsViewManager::ReactContext() noexcept
    {
        return m_reactContext;
    }

    void RNMapsViewManager::ReactContext(IReactContext reactContext) noexcept
    {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> RNMapsViewManager::NativeProps() noexcept
    {
        return winrt::RNMaps::implementation::RNMapsModule::NativeProps();
    }

    void RNMapsViewManager::UpdateProperties(
        FrameworkElement const &view,
        IJSValueReader const &propertyMapReader) noexcept
    {
        if (auto module = view.try_as<winrt::RNMaps::RNMapsModule>())
        {
            module.UpdateProperties(propertyMapReader);
        }
    }
    // IViewManagerWithExportedEventTypeConstants
    ConstantProviderDelegate RNMapsViewManager::ExportedCustomBubblingEventTypeConstants() noexcept
    {
        return winrt::RNMaps::implementation::RNMapsModule::ExportedCustomBubblingEventTypeConstants();
    }

    ConstantProviderDelegate RNMapsViewManager::ExportedCustomDirectEventTypeConstants() noexcept
    {
        return winrt::RNMaps::implementation::RNMapsModule::ExportedCustomDirectEventTypeConstants();
    }

    // IViewManagerWithCommands
    IVectorView<hstring> RNMapsViewManager::Commands() noexcept
    {
        return winrt::RNMaps::implementation::RNMapsModule::Commands();
    }

    void RNMapsViewManager::DispatchCommand(
        FrameworkElement const &view,
        winrt::hstring const &commandId,
        winrt::IJSValueReader const &commandArgsReader) noexcept
    {
        if (auto module = view.try_as<winrt::RNMaps::RNMapsModule>())
        {
            module.DispatchCommand(commandId, commandArgsReader);
        }
    }
}
