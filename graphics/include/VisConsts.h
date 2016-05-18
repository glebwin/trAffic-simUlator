#ifndef TRAFFIC_SIMULATOR_VISCONSTS_H
#define TRAFFIC_SIMULATOR_VISCONSTS_H


#include <SFML/Graphics/Color.hpp>

struct VisConsts {
public:

    const sf::Color asphalt_col;
    const sf::Color road_outline_col;
    const sf::Color marking_col;
    const double road_outline_thickness;
    double scale;
    const double marking_thickness;
    const double dash_len;
    const double dash_padd;
    const double dash_thick;
    const double car_width;

private:

    VisConsts() : asphalt_col(130, 130, 130), road_outline_col(230, 230, 230),
                  marking_col(250, 250, 250), road_outline_thickness(0.08), marking_thickness(0.2),
                  dash_len(0.8), dash_padd(0.2), dash_thick(0.1), car_width(0.8) {}
    VisConsts(const VisConsts&);
    VisConsts& operator=(VisConsts&);

public:

    static VisConsts& get() {
        static VisConsts instance;
        return instance;
    }
};


#endif
