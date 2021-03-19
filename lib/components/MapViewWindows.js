import * as React from 'react';
import { requireNativeComponent, View, Text } from 'react-native';

const RNMapWindows = requireNativeComponent('RNMapsWindowsTest', RNMapViewWindows, {
  nativeOnly: {
    nativeID: true,
    onChange: true
  }
});

export default class RNMapViewWindows extends React.Component {
  render() {
    return (
      <RNMapWindows style={{ backgroundColor: 'transparent', width: 500, height: 250}}/>
    );
  }
}
