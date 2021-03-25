#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "RNMapIconViewManager.h"
#include "RNMapIcon.h"

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
    winrt::hstring RNMapIconViewManager::Name() noexcept
    {
        return L"RNMapIconWindowsTest";
    }

    winrt::FrameworkElement RNMapIconViewManager::CreateView() noexcept
    {
        return winrt::RNMaps::RNMapIconModule(m_reactContext);
    }

    // IViewManagerWithReactContext
    winrt::IReactContext RNMapIconViewManager::ReactContext() noexcept
    {
        return m_reactContext;
    }

    void RNMapIconViewManager::ReactContext(IReactContext reactContext) noexcept
    {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> RNMapIconViewManager::NativeProps() noexcept
    {
        return winrt::RNMaps::implementation::RNMapIconModule::NativeProps();
    }

    void RNMapIconViewManager::UpdateProperties(
        FrameworkElement const &view,
        IJSValueReader const &propertyMapReader) noexcept
    {
        if (auto module = view.try_as<winrt::RNMaps::RNMapIconModule>())
        {
            module.UpdateProperties(propertyMapReader);
        }
    }
    // IViewManagerWithExportedEventTypeConstants
    ConstantProviderDelegate RNMapIconViewManager::ExportedCustomBubblingEventTypeConstants() noexcept
    {
        return winrt::RNMaps::implementation::RNMapIconModule::ExportedCustomBubblingEventTypeConstants();
    }

    ConstantProviderDelegate RNMapIconViewManager::ExportedCustomDirectEventTypeConstants() noexcept
    {
        return winrt::RNMaps::implementation::RNMapIconModule::ExportedCustomDirectEventTypeConstants();
    }

    // IViewManagerWithCommands
    IVectorView<hstring> RNMapIconViewManager::Commands() noexcept
    {
        return winrt::RNMaps::implementation::RNMapIconModule::Commands();
    }

    void RNMapIconViewManager::DispatchCommand(
        FrameworkElement const &view,
        winrt::hstring const &commandId,
        winrt::IJSValueReader const &commandArgsReader) noexcept
    {
        if (auto module = view.try_as<winrt::RNMaps::RNMapIconModule>())
        {
            module.DispatchCommand(commandId, commandArgsReader);
        }
    }
}
