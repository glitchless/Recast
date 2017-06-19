//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_ITEMPERATUREWORLDPOINTPRIORITIZABLE_H
#define RECAST_ITEMPERATUREWORLDPOINTPRIORITIZABLE_H


/**
 * Mixin to temperature world.
 * Makes temperature world to know which points are more important.
 * 
 * @tparam T Base temperature world class.
 */
template<typename T>
class ITemperatureWorldPointPrioritizable : public virtual T {
public:
    /**
     * Marks point where there is something important.
     * 
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     */
    virtual void addPriorityPoint(Coord x, Coord y, Coord z) = 0;
    
    /**
     * Unmarks point where there is something important.
     * 
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     */
    virtual void removePriorityPoint(Coord x, Coord y, Coord z) = 0;
};


#endif //RECAST_ITEMPERATUREWORLDPOINTPRIORITIZABLE_H