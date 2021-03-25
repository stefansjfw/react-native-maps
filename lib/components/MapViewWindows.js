import * as React from 'react';
import { requireNativeComponent, View, Text } from 'react-native';

const RNMapWindows = requireNativeComponent('RNMapsWindowsTest', RNMapViewWindows, {
  nativeOnly: {
    nativeID: true,
    onChange: true
  }
});

const RNPolylineWindows = requireNativeComponent('RNPolylineWindowsTest', RNPolylineViewWindows, {
  nativeOnly: {
    nativeID: true,
    onChange: true
  }
});

const RNMapIconWindows = requireNativeComponent('RNMapIconWindowsTest', RNMapIconViewWindows, {
  nativeOnly: {
    nativeID: true,
    onChange: true
  }
});

export default class RNMapViewWindows extends React.Component {
  render() {
    return (
      <RNMapWindows style={{ backgroundColor: 'transparent', width: 500, height: 250}}>
        {this.props.children}
      </RNMapWindows>
    );
  }
}

export class RNPolylineViewWindows extends React.Component {
  render() {
    return (
      <RNPolylineWindows {...this.props}/>
    );
  }
}

export class RNMapIconViewWindows extends React.Component {
  render() {
    return (
      <RNMapIconWindows {...this.props}/>
    );
  }
}
