//
//  UIImage+IconFont.swift
//  ZLGitHubClient
//
//  Created by 朱猛 on 2022/5/28.
//  Copyright © 2022 ZM. All rights reserved.
//

import Foundation
import UIKit
import CoreGraphics

public extension UIImage {
    
    @objc static func iconFontImage(withText: String,
                                    fontSize: CGFloat ,
                                    imageSize: CGSize,
                                    color: UIColor) -> UIImage? {
      
        let renderer = UIGraphicsImageRenderer(size: imageSize)
        
        let image = renderer.image { context in
            let attributedString = NSAttributedString(string: withText,
                                                      attributes: [.foregroundColor:color,
                                                                   .font:UIFont.zlIconFont(withSize: fontSize)])
            
            attributedString.draw(at: CGPoint(x: (imageSize.width - attributedString.size().width) / 2,
                                              y: (imageSize.height - attributedString.size().height) / 2))
        }
            
        return image
    }
    
    @objc static func iconFontImage(withText: String,
                                    fontSize: CGFloat ,
                                    color: UIColor) -> UIImage? {
        return UIImage.iconFontImage(withText: withText,
                                     fontSize: fontSize,
                                     imageSize: CGSize(width: fontSize, height: fontSize),
                                     color: color)
    }
}
