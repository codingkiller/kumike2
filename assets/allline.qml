import bb.cascades 1.2
import bb.data 1.0
import NetworkBus 1.0
import busline 1.0
//NavigationPane {
//    id: navigationPane2

Page {
//    attachedObjects: ComponentDefinition {
//        id: pageDefinition2;
//        source: "resultPage.qml"
//    }
    onCreationCompleted: {
        networkBus.process ? thirdIndicator.start() : thirdIndicator.stop();
      //  console.log("resultpage.qml:endstation:"+networkBus.end_station);
    }
	id: thirdPage
    titleBar: TitleBar {
        id: thirdtitlebar
        kind: TitleBarKind.FreeForm
        kindProperties: FreeFormTitleBarKindProperties {
            Container{
                id:thirdtitlebarcontainer
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 20
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: ""
                    minWidth: 290
                }
                Label {
                    id: secondtitlebarcontainerlabel
                    text : networkBus.process ? qsTr("查询中 ") : qsTr("所有线路 ")
                    textStyle {
                        color: Color.White
                        fontSize: FontSize.XLarge
                    }
                    horizontalAlignment: HorizontalAlignment.Center
                    layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                }
            }
        }
    }

    Container {
        leftPadding: 50
        rightPadding: 50
        ActivityIndicator {
            id: thirdIndicator
            minHeight: 600
            minWidth: 768
            visible: networkBus.process
            onVisibleChanged: {
                thirdIndicator.visible ? thirdIndicator.start() : thirdIndicator.stop();
            }
        }
        ListView {
        //    property NetworkBus networkBus : networkBus
            id: localDataList
          //  visible: !networkBus.process
            dataModel: networkBus.alllineDataModel
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
                        }
                        
                        Divider {
                        
                        }
                    }
                
                }
            
            ]
            onTriggered: {
                networkBus.get_lines_by_city(listDialog.value,networkBus.alllineDataModel.data(indexPath).line_name)
                var page = pageDefinition.createObject()
                navigationPane.push(page)
            }
        //}
    }
}
}