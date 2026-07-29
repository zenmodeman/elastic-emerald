#ifndef GUARD_CONFIG_RESOURCE_MODE_H
#define GUARD_CONFIG_RESOURCE_MODE_H

// Move-service points available when a new game begins.
#define RESOURCE_MODE_BASE_POINTS              3
#define RESOURCE_MODE_MONOTYPE_BASE_POINTS     5

// Every badge grants this many points before any affordability assistance.
#define RESOURCE_MODE_POINTS_PER_BADGE          1
#define RESOURCE_MODE_MONOTYPE_POINTS_PER_BADGE 2
#define RESOURCE_MODE_AFFORDANCE_POINTS         1

// Badges 1-4 assist after any depletion. From badge 5 onward, the required
// depletion starts at 2 and increases by 1 with each badge.
#define RESOURCE_MODE_LATE_BADGE_START         5
#define RESOURCE_MODE_EARLY_DEPLETION_REQUIRED 1
#define RESOURCE_MODE_LATE_DEPLETION_OFFSET    3

#endif // GUARD_CONFIG_RESOURCE_MODE_H
