import bb.cascades 1.0
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
                Label {
                	text : !networkBus.line_name ? qsTr("查询结果") : networkBus.line_name;
                    textStyle {
                        color: Color.White
                        fontSize: FontSize.XLarge
                      //  textAlign: TextAlign.Right
                    }
                    horizontalAlignment: HorizontalAlignment.Center
                    layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                    onTextChanged: {
                        myIndicator.stop();
                    }
                }
                }
        }
     //   title: networkBus.line_name ? qsTr("查询结果") : networkBus.line_name;
    }
    Container {
        Container {
            layout: StackLayout { orientation: LayoutOrientation.TopToBottom }
            topPadding: 20
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            
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
                //  accessibility.name: "TODO: Add property content"
                onSelectedIndexChanged: {
                    networkBus.changeBusLine(selectedValue)
                }
            }
            Divider {
                //   visible: true
                //   accessibility.name: "TODO: Add property content"
            }
        }
        
        
        Container {
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
            topPadding: 20
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            minHeight: 820
            ActivityIndicator {
                id: myIndicator
                minHeight: 600                
            }
            TextArea {
                text: networkBus.all_station
            }
        }
        Container {
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
            topPadding: 20
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            Label {
                text: qsTr("首末班 "+networkBus.begin_time+"-"+networkBus.end_time+"     全程 "+networkBus.price+"元 ")
            }
        
        }
    }

//    attachedObjects: [
//        NetworkBus {
//            id: networkBus
//        
//        }
//    ]
    onCreationCompleted: {
        myIndicator.start();
        
        console.log("resultpage.qml:endstation:"+networkBus.end_station);
    }
    
}