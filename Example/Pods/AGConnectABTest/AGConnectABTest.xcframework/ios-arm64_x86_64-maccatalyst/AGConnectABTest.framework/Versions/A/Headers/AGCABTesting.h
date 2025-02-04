//
//  Copyright (c) Huawei Technologies Co., Ltd. 2020. All rights reserved
//

#import <Foundation/Foundation.h>
#import "AGCABTestError.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * AB 测试 入口类
 */
@interface AGCABTesting : NSObject

/**
 * 初始化方法
 *
 * @param originService 服务名称，根据服务名称获取对应的实例，支持`REMOTE-CONFIG`等
 * @return 返回AB测试实例
 */
+ (instancetype)getInstanceWithService:(NSString *)originService;

/**
 * 替换参与的实验，非参与的实验则进行删除
 *
 * @param replacementExperiments
 * 实验信息的Dictionary，Dictionary中要有`experimentId`,`variantId`等字段
 * @param error 错误
 */
- (void)replaceAllExperiments:(NSArray<NSDictionary<NSString *, id> *> *)replacementExperiments
                        error:(NSError **)error;

/**
 * 删除所有实验
 * @param error 错误
 */
- (void)removeAllExperiments:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
