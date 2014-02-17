import bb.cascades 1.2

Page {
    titleBar: TitleBar {
        id: secondtitlebar
        kind: TitleBarKind.FreeForm
        kindProperties: FreeFormTitleBarKindProperties {
            Container{
                id:secondtitlebarcontainer
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                topPadding: 20
                Label {
                    text: ""
                    minWidth: 290
                }
                Label {
                    id: secondtitlebarcontainerlabel
                    text :  qsTr("查询中 ") ;
                    textStyle {
                        color: Color.White
                        fontSize: FontSize.XLarge
                    }
                    horizontalAlignment: HorizontalAlignment.Center
                    layoutProperties: StackLayoutProperties { spaceQuota: 1 }
                }
                ImageButton {
                    rightPadding: 0
                    rightMargin: 0
                    defaultImageSource: "asset:///images/ic_reload.png"
                }
            }
        }
    }
    Container {
        ListView {
            dataModel: XmlDataModel { source: "bus_station.xml" }
            rootIndexPath: [1]
         //   rotationZ: 90
            layout: StackListLayout {
                orientation: LayoutOrientation.TopToBottom
            }
            listItemComponents: [
                ListItemComponent {
                    id: listitem
                    type: "item"
                    Container {
                        
                    
                    Container {
                        leftPadding: ListItem.indexPath
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
        
                        ImageView {
                            imageSource: ListItemData.image
                        }
                        Label {
                            text: ListItemData.title
                          //  textStyle.color: Color.Green
                          	textStyle.fontWeight: FontWeight.W100
                          	textStyle.fontSize: FontSize.Large
                        }
                        
                        /*TextArea {
                            maxWidth: 82
                            text: ListItemData.title
                            horizontalAlignment: HorizontalAlignment.Left
                            verticalAlignment: VerticalAlignment.Top
                        }*/
                    }
                    Container {
                        background: Color.Blue
                        preferredHeight: 1
                        preferredWidth: 768
                    }
                }
                }
            ]
        }
    }
}
