require 'json'

package = JSON.parse(File.read(File.join(__dir__, 'version.json')))

Pod::Spec.new do |s|
  s.name         = "AppierFramework"
  s.version      = package['version']
  s.summary      = "AppierFramework is the library for Appier Enterprise Solutions."
  s.homepage     = "https://www.appier.com/en/index.html"
  s.documentation_url = "https://docs.aiqua.appier.com/docs"
  s.license    = { :type => "MIT", :file => "Classes/LICENSE" }
  s.author       = { "appier" => "rex.chen@appier.com" }
  s.platform     = :ios, '8.0'
  s.source       = { :git => "https://github.com/appier/appier-ios-framework.git", :tag => "v#{s.version}"}
  s.ios.vendored_frameworks = 'Appier.framework'
  s.frameworks = 'AdSupport', 'CoreTelephony', 'SystemConfiguration', 'CoreLocation', 'ImageIO', 'MobileCoreServices'
  s.requires_arc = true
end
