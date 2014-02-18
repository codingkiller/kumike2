import bb.cascades 1.0
import bb.data 1.0
import NetworkBus 1.0
Page {

    id: secondPage
    titleBar: TitleBar {
        id: secondtitlebar
        kind: TitleBarKind.FreeForm
        kindProperties: FreeFormTitleBarKindProperties {
            Container{
                id:secondtitlebarcontainer
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 20
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: ""
                    minWidth: 270
                }
                Label {
                    id: secondtitlebarcontainerlabel
                	text : networkBus.process ? qsTr("查询中 ") : networkBus.line_name;
                    textStyle {
                        color: Color.White
                        fontSize: FontSize.XLarge
                    }
                    horizontalAlignment: HorizontalAlignment.Center
                    layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                }
                ImageButton {
                 //   rightPadding: 0
                 //   rightMargin: 0
                //   defaultImageSource:  
                   defaultImageSource: "asset:///images/ic_reload.png"
                   
                    onClicked: {
                        networkBus.reloadGPSData();
                    }
                }
                }
        }
    }
    Container {
        /*Container {
            background: Color.Red
            preferredHeight: 300
        }*/
        Container {
            layout: StackLayout { orientation: LayoutOrientation.TopToBottom }
            topPadding: 20
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
        //    visible: !networkBus.process
            Label {
                id: errorInfo
                text: networkBus.error
                visible:networkBus.error
            }

            SegmentedControl {
                id: selectLine
                Option {
                    value: 0
                    text: "开往"+networkBus.to_station_one
                }
                Option {
                    value: 1
                    text: "开往"+networkBus.to_station_two
                }
                onSelectedIndexChanged: {
                    networkBus.changeBusLine(selectedValue);
                }
            }
            Divider {
                
            }
            
            ActivityIndicator {
                id: myIndicator
                minHeight: 600
                minWidth: 768
                visible: networkBus.process
                onVisibleChanged: {
                    myIndicator.visible ? myIndicator.start() : myIndicator.stop();
                }
            }
        }

        Container {
            id: thirdContainer
            layout: StackLayout { orientation: LayoutOrientation.TopToBottom }
            topPadding: 20
            maxHeight: 500
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            ListView {
                id: stationListView
                visible: !networkBus.process
                dataModel: networkBus.dataModel
                layout: StackListLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                topPadding: 0
                listItemComponents: [
                    ListItemComponent {
                        Container {
                            layout: StackLayout {
                                orientation: LayoutOrientation.TopToBottom
                            }
                            minWidth: 120
                            Container {
                                minWidth: 120
                                maxHeight: 27
                                bottomPadding: 0
                                topPadding: 0
                                verticalAlignment: VerticalAlignment.Bottom
                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }
                                Label {
                                    maxHeight: 3
                                    minWidth: ListItemData.bus_state == "cur_station" ? 0 : 50
                                }
                                ImageView {
                                    maxHeight: 27
                                    imageSource: "asset:///images/ic_bus_enable.jpg"
                                    visible: ListItemData.bus_state
                                }
                            }
                            Divider {
                                minWidth: 120
                                maxWidth: 120
                                minHeight: 1
                                maxHeight: 2
                      //          topPadding: 0
                            }
                            Container {
                                minWidth: 120
                                topPadding: 0
                                horizontalAlignment: HorizontalAlignment.Left
                                verticalAlignment: VerticalAlignment.Top
                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }
                                TextArea {
                                    topPadding: 0
                                    maxWidth: 80
                                    text: ListItemData.name.toString()
                                    editable: false
                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Top
                                }
                            }
                        }
                        
                    }

                ]
            }
        }
        Container {
            visible: !networkBus.process
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
            topPadding: 20
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            Label {
                text: qsTr("首末班 "+networkBus.begin_time+"-"+networkBus.end_time+"     全程 "+networkBus.price+"元 ")
            }
        
        }
    }
    onCreationCompleted: {
        networkBus.process ? myIndicator.start() : myIndicator.stop();
        console.log("resultpage.qml:endstation:"+networkBus.end_station);
    }
    
}