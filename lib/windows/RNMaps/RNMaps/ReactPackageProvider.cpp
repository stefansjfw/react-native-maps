#include "pch.h"
#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "RNMapsViewManager.h"
#include "RNPolylineViewManager.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::RNMaps::implementation
{
  void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
  {
    packageBuilder.AddViewManager(L"RNMapsViewManager", []() { return winrt::make<RNMapsViewManager>(); });
    packageBuilder.AddViewManager(L"RNPolylineViewManager", []() { return winrt::make<RNPolylineViewManager>(); });
  }
}
