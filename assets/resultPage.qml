import bb.cascades 1.0
import NetworkBus 1.0

Page {
    titleBar: TitleBar {
        kind: TitleBarKind.FreeForm
        kindProperties: FreeFormTitleBarKindProperties {
            Container {
                layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
                topPadding: 20
                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Center
                ImageView {
                    imageSource: "asset:///images/ic_previous.png"
                    horizontalAlignment: HorizontalAlignment.Left
                    onTouch: {
                      //  busResultSheet.close();
                    }
                }
                Label {
                    text: networkBus.line_name
                    textStyle {
                        color: Color.White
                        fontSize: FontSize.XLarge
                        textAlign: TextAlign.Right
                    }
                    maxWidth: 400
                    horizontalAlignment: HorizontalAlignment.Right
                    layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                }
            
            }
        }
    }
    Container {
        Container {
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
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
        }
        
        Divider {
            //   visible: true
            //   accessibility.name: "TODO: Add property content"
        }
        Container {
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
            topPadding: 20
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            minHeight: 800
        }
        Container {
            layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
            topPadding: 20
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            Label {
                text: qsTr("首末班 "+networkBus.begin_time+"-"+networkBus.end_time+" 全程 "+networkBus.price+"元 ")
            }
        
        }
    }
    actions: [  
        ActionItem {  
            title: "返回"  
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
             //   busResultSheet.close();  
            }
        }
    ]
    attachedObjects: [
        NetworkBus {
            id: networkBus
        
        }
    ]
    onCreationCompleted: {
        console.log("resultpage.qml:endstation:"+networkBus.end_station);
    }
}