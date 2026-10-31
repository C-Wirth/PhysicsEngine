#include "AbstractForce2D.hh"

class AppliedForce2D : public AbstractForce2D
{
public:
    AppliedForce2D()
    {
    }

    auto applyForce(AbstractElement2D& element) -> void override
    {
    #TODO implement me

    #  TODO define forces in the toml file like:
        /**
         * [[ AppliedForces2D ]]
         * name <string>
         * force (N) [x, y]
         * particles [p1, p2 , ...]
         * duration <double>
         * start_times [t1, t2, ...]
         */

    }

private:
};
