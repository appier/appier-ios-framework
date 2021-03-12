require 'json'

package = JSON.parse(File.read(File.join(__dir__, 'version.json')))

Pod::Spec.new do |s|
  s.name         = "AppierExtensionFramework"
  s.version      = package['version'][1..-1]
  s.summary      = "AppierExtensionFramework is the library for Appier Enterprise Solutions."
  s.homepage     = "https://www.appier.com"
  s.documentation_url = "https://docs.aiqua.appier.com/docs"
  s.license    = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "Appier" => "shiv.raj@appier.com" }
  s.platform     = :ios, '10.0'
  s.source       = { :git => "https://github.com/appier/appier-ios-framework.git", :tag => package['version']}
  s.ios.vendored_frameworks = 'AppierExtension.xcframework'
  s.requires_arc = true
end
