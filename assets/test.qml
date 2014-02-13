import bb.cascades 1.2

Page {
    Container {
        ListView {
            dataModel: XmlDataModel { source: "bus_station.xml" }
            rootIndexPath: [1]
         //   rotationZ: 90
            layout: StackListLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            listItemComponents: [
                ListItemComponent {
                    id: listitem
                    type: "item"
                    Container {
                        leftPadding: ListItem.indexPath
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
        
                        ImageView {
                            imageSource: ListItemData.image
                        }
                        Label {
                            text: listitem.ListItem.indexPath
                        }
                        TextArea {
                            maxWidth: 82
                            text: ListItemData.title
                            horizontalAlignment: HorizontalAlignment.Left
                            verticalAlignment: VerticalAlignment.Top
                        }
                    }
                }
            ]
        }
    }
}
