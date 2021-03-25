#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "RNPolylineViewManager.h"
#include "RNPolyline.h"

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
  winrt::hstring RNPolylineViewManager::Name() noexcept
  {
    return L"RNPolylineWindowsTest";
  }

  winrt::FrameworkElement RNPolylineViewManager::CreateView() noexcept
  {
    return winrt::RNMaps::RNPolylineModule(m_reactContext);
  }

  // IViewManagerWithReactContext
  winrt::IReactContext RNPolylineViewManager::ReactContext() noexcept
  {
    return m_reactContext;
  }

  void RNPolylineViewManager::ReactContext(IReactContext reactContext) noexcept
  {
    m_reactContext = reactContext;
  }

  // IViewManagerWithNativeProperties
  IMapView<hstring, ViewManagerPropertyType> RNPolylineViewManager::NativeProps() noexcept
  {
    return winrt::RNMaps::implementation::RNPolylineModule::NativeProps();
  }

  void RNPolylineViewManager::UpdateProperties(
      FrameworkElement const &view,
      IJSValueReader const &propertyMapReader) noexcept
  {
    if (auto module = view.try_as<winrt::RNMaps::RNPolylineModule>())
    {
      module.UpdateProperties(propertyMapReader);
    }
  }
  // IViewManagerWithExportedEventTypeConstants
  ConstantProviderDelegate RNPolylineViewManager::ExportedCustomBubblingEventTypeConstants() noexcept
  {
    return winrt::RNMaps::implementation::RNPolylineModule::ExportedCustomBubblingEventTypeConstants();
  }

  ConstantProviderDelegate RNPolylineViewManager::ExportedCustomDirectEventTypeConstants() noexcept
  {
    return winrt::RNMaps::implementation::RNPolylineModule::ExportedCustomDirectEventTypeConstants();
  }

  // IViewManagerWithCommands
  IVectorView<hstring> RNPolylineViewManager::Commands() noexcept
  {
    return winrt::RNMaps::implementation::RNPolylineModule::Commands();
  }

  void RNPolylineViewManager::DispatchCommand(
      FrameworkElement const &view,
      winrt::hstring const &commandId,
      winrt::IJSValueReader const &commandArgsReader) noexcept
  {
    if (auto module = view.try_as<winrt::RNMaps::RNPolylineModule>())
    {
      module.DispatchCommand(commandId, commandArgsReader);
    }
  }
}
