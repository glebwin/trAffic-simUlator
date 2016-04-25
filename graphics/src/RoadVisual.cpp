#include "../../core/include/Crossroad.h"
#include "../../core/include/Road.h"
#include "../include/RoadVisual.h"
#include "../include/VisConsts.h"

RoadVisual::RoadVisual(sf::RenderWindow *window, const Road *road)
        : window(window), road(road) {
    set_sprite_asphalt();
    set_sprite_solid_lane();
}

void RoadVisual::draw() {
    window->draw(sprite_asphalt);
    window->draw(sprite_solid_lane);
}

void RoadVisual::set_sprite_asphalt() {
    Crossroad *crossroad1 = road->get_beg_crossroad();
    Crossroad *crossroad2 = road->get_end_crossroad();
    auto cr1_tl_corner = crossroad1->get_top_left_corner();
    auto cr1_br_corner = crossroad1->get_bott_right_corner();
    auto cr2_tl_corner = crossroad2->get_top_left_corner();
    auto cr2_br_corner = crossroad2->get_bott_right_corner();

    std::pair<int, int> top_left_corner(std::min(cr1_br_corner.first, cr2_br_corner.first),
                                        std::min(cr1_tl_corner.second, cr2_tl_corner.second));
    std::pair<int, int> bott_right_corner(std::max(cr1_tl_corner.first, cr2_tl_corner.first),
                                          std::max(cr1_br_corner.second, cr2_br_corner.second));

    sprite_asphalt.setPosition(top_left_corner.first, top_left_corner.second);
    sprite_asphalt.setSize(sf::Vector2f(bott_right_corner.first - top_left_corner.first,
                                         bott_right_corner.second - top_left_corner.second));
    sprite_asphalt.setOutlineThickness(VisConsts::get().road_outline_thickness);
    sprite_asphalt.setFillColor(VisConsts::get().asphalt_col);
    sprite_asphalt.setOutlineColor(VisConsts::get().road_outline_col);

    sprite_asphalt.setScale(VisConsts::get().scale, VisConsts::get().scale);
    sprite_asphalt.setPosition(sf::Vector2f(sprite_asphalt.getPosition().x * VisConsts::get().scale,
                                            sprite_asphalt.getPosition().y * VisConsts::get().scale));
}

void RoadVisual::set_sprite_solid_lane() {
    Crossroad *beg_crossroad = road->get_beg_crossroad();
    Crossroad *end_crossroad = road->get_end_crossroad();
    bool horizontal = (beg_crossroad->get_top_left_corner().second ==
                       end_crossroad->get_top_left_corner().second);

    if(horizontal) {
        int road_width = beg_crossroad->get_bott_right_corner().second - beg_crossroad->get_top_left_corner().second;
        unsigned long forward_lanes_num = road->get_forward_lanes().size();
        unsigned long backward_lanes_num = road->get_backward_lanes().size();
        double mid;
        if(beg_crossroad->get_top_left_corner().first < end_crossroad->get_top_left_corner().first)
            mid = beg_crossroad->get_top_left_corner().second + road_width *
                  (static_cast<double>(forward_lanes_num) / (forward_lanes_num+backward_lanes_num));
        else
            mid = beg_crossroad->get_top_left_corner().second + road_width *
                  (static_cast<double>(backward_lanes_num) / (forward_lanes_num+backward_lanes_num));

        int x_left = std::min(beg_crossroad->get_bott_right_corner().first,
                              end_crossroad->get_bott_right_corner().first);
        int x_right = std::max(beg_crossroad->get_top_left_corner().first,
                               end_crossroad->get_top_left_corner().first);
        sprite_solid_lane.setPosition(x_left, mid - VisConsts::get().marking_thickness / 2);
        sprite_solid_lane.setSize(sf::Vector2f((x_right - x_left), VisConsts::get().marking_thickness));
    }
    else {
        int road_width = beg_crossroad->get_bott_right_corner().first - beg_crossroad->get_top_left_corner().first;
        unsigned long forward_lanes_num = road->get_forward_lanes().size();
        unsigned long backward_lanes_num = road->get_backward_lanes().size();
        double mid;
        if(beg_crossroad->get_top_left_corner().second < end_crossroad->get_top_left_corner().second)
            mid = beg_crossroad->get_top_left_corner().first + road_width *
                                                                (static_cast<double>(forward_lanes_num) / (forward_lanes_num+backward_lanes_num));
        else
            mid = beg_crossroad->get_top_left_corner().first + road_width *
                                                                (static_cast<double>(backward_lanes_num) / (forward_lanes_num+backward_lanes_num));

        int y_top = std::min(beg_crossroad->get_bott_right_corner().second,
                             end_crossroad->get_bott_right_corner().second);
        int y_bott = std::max(beg_crossroad->get_top_left_corner().second,
                              end_crossroad->get_top_left_corner().second);
        sprite_solid_lane.setPosition(mid - VisConsts::get().marking_thickness / 2, y_top);
        sprite_solid_lane.setSize(sf::Vector2f((y_bott - y_top), VisConsts::get().marking_thickness));
    }

    sprite_solid_lane.setPosition(sf::Vector2f(sprite_solid_lane.getPosition().x * VisConsts::get().scale,
                                               sprite_solid_lane.getPosition().y * VisConsts::get().scale));
    sprite_solid_lane.setScale(VisConsts::get().scale, VisConsts::get().scale);
    sprite_solid_lane.setFillColor(VisConsts::get().marking_col);
}
