// swift-tools-version:5.7.1
import PackageDescription

let package = Package(
  name: "AppierFramework",
  platforms: [
    .iOS(.v10)
  ],
  products: [
    .library(
      name: "AppierFramework",
      targets: [
        "Appier"
      ]
    ),
    .library(
      name: "AppierExtensionFramework",
      targets: [
        "AppierExtension"
      ]
    )
  ],
  targets: [
    .binaryTarget(
      name: "Appier",
      path: "Appier.xcframework"
    ),
    .binaryTarget(
      name: "AppierExtension",
      path: "AppierExtension.xcframework"
    )
  ]
)
