//
//  Copyright (c) Huawei Technologies Co., Ltd. 2020. All rights reserved
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 存储数据的类，在fetch方法中返回的ConfigValues对象用于调用apply()方法。
 * 针对fetch方法返回的ConfigValues对象，只是从云端同步下来的数据，不包含default数据。
 */
@interface AGCConfigValues : NSObject

/**
 * 数据中是否包含对应Key值
 * @param key 远程配置参数Key值
 * @return 是否包含Key
 */
- (BOOL)contain:(NSString *)key;

/**
 * 返回Key对应的BOOL类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (BOOL)valueAsBool:(NSString *)key NS_SWIFT_NAME(valueAsBool(key:));

/**
 * 返回Key对应的NSNumber类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (NSNumber *)valueAsNumber:(NSString *)key NS_SWIFT_NAME(valueAsNumber(key:));

/**
 * 返回Key对应的NSString类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (NSString *)valueAsString:(NSString *)key NS_SWIFT_NAME(valueAsString(key:));

/**
 * 返回Key对应的NSData类型的Value值
 * @param key 远程配置参数Key值
 * @return 对应的value值，若不包含Key则返回默认值
 */
- (NSData *)valueAsData:(NSString *)key NS_SWIFT_NAME(valueAsData(key:));

@end

NS_ASSUME_NONNULL_END
