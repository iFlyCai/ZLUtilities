//
//  Copyright (c) Huawei Technologies Co., Ltd. 2020. All rights reserved
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/**
 * AB测试错误码枚举
 */
typedef NS_ENUM(NSUInteger, AGCABTestErrorCode) {
    /**
     * HA SDK 创建失败
     */
    AGCABTestErrorCodeAnalyticsSDKError = 1,

    /**
     * 传入的实验Map中缺少必要的Key值
     */
    AGCABTestErrorCodeNotExistKey = 2,

    /**
     * 传入的实验Map中Value值格式不正确
     */
    AGCABTestErrorCodeNumberFormatError = 3
};

/**
 * AB测试错误码
 */
@interface AGCABTestError : NSError

@end

NS_ASSUME_NONNULL_END
