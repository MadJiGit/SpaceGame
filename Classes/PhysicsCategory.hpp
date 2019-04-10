//
//  PhysicsCategory.hpp
//  SpaceGame-mobile
//
//  Created by Madji on 15.06.18.
//

#ifndef PhysicsCategory_hpp
#define PhysicsCategory_hpp

#include <stdio.h>

enum class PhysicsCategory {
    None = 0,
    RangerPC = (1 << 0),    // 1
    EnemyPC = (1 << 1), // 2
    ShootPC = (1 << 0),
    All = PhysicsCategory::RangerPC | PhysicsCategory::EnemyPC | PhysicsCategory::ShootPC// 3
};


#endif /* PhysicsCategory_hpp */
