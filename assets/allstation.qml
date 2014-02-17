import bb.cascades 1.2
NavigationPane {
    id: navigationPane

Page {
    attachedObjects: ComponentDefinition {
        id: pageDefinition;
        source: "resultPage.qml"
    }

    Container {
        ListView {
            property NetworkBus networkBus : networkBus
            id: localDataList
            visible: !networkBus.process
            dataModel: networkBus.localDataModel
            layout: StackListLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            topPadding: 0
            listItemComponents: [
                ListItemComponent {
                    Container {
                        id: rootItem
                        layout: StackLayout {
                            orientation: LayoutOrientation.TopToBottom
                        }
                        minWidth: 120
                        Container {
                            minWidth: 120
                            bottomPadding: 0
                            verticalAlignment: VerticalAlignment.Bottom
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            Container {
                                //   minWidth: 568
                                //  maxWidth: 568
                                preferredWidth: 568
                                Label {
                                    text: qsTr(ListItemData.line_name)
                                }
                                Label {
                                    text: qsTr(ListItemData.start_station + "  -  " + ListItemData.end_station)
                                    textStyle.fontStyle: FontStyle.Italic
                                    textStyle.fontSize: FontSize.Small
                                }
                            }
                            Container {
                                rightPadding: 0
                                horizontalAlignment: HorizontalAlignment.Right
                                verticalAlignment: VerticalAlignment.Center
                                //  background: Color.Blue
                                
                                /*Button {
                                 imageSource: "asset:///images/ic_delete.png"
                                 maxWidth: 70
                                 onClicked: {
                                 rootItem.ListItem.view.networkBus.deleteRecord(ListItemData.record_id)
                                 }
                                 }*/
                                ImageButton {
                                    defaultImageSource: "asset:///images/ic_clear.png"
                                    //  maxWidth: 70
                                    onClicked: {
                                        var page = pageDefinition.createObject()
                                        navigationPane.push(page)
                                        rootItem.ListItem.view.networkBus.deleteRecord(ListItemData.record_id)
                                    }
                                }
                            }
                        
                        
                        }
                        
                        Divider {
                        
                        }
                    }
                
                }
            
            ]
        }
    }
}
}