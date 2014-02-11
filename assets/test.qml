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
                    type: "header"
                    Label {
                        text: ListItemData.title
                    }
                },
                ListItemComponent {
                    type: "item"
                    Container {
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        ImageView {
                            imageSource: ListItemData.image
                        }
                        TextArea {
                            maxWidth: 80
                            text: ListItemData.title
                        }
                    }
                }
            ]
        }
    }
}
