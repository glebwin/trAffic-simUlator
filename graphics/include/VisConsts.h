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
                  marking_col(250, 250, 250), road_outline_thickness(80), marking_thickness(200),
                  dash_len(800), dash_padd(200), dash_thick(100), car_width(800) {}
    VisConsts(const VisConsts&);
    VisConsts& operator=(VisConsts&);

public:

    static VisConsts& get() {
        static VisConsts instance;
        return instance;
    }
};


#endif
