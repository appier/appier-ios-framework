// swift-tools-version:5.3
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
        "AppierFramework"
      ]
    ),
    .library(
      name: "AppierExtensionFramework",
      targets: [
        "AppierExtensionFramework"
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
