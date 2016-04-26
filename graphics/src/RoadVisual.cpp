#include "../../core/include/Crossroad.h"
#include "../../core/include/Road.h"
#include "../include/RoadVisual.h"
#include "../include/VisConsts.h"

RoadVisual::RoadVisual(sf::RenderWindow *window, const Road *road)
        : window(window), road(road) {
    set_sprite_asphalt();
    set_sprite_solid_line();
    set_sprites_dashed_lines();
}

#include <fstream>

void RoadVisual::draw() {
    window->draw(sprite_asphalt);
    window->draw(sprite_solid_line);

    for(double x : dashed_line_xs)
        for(double y : dashed_line_ys) {
            sprite_dashed_line.setPosition(x, y);
            window->draw(sprite_dashed_line);
        }
}

void RoadVisual::set_sprite_asphalt() {
    Crossroad *crossroad1 = road->get_beg_crossroad();
    Crossroad *crossroad2 = road->get_end_crossroad();
    auto cr1_tl_corner = crossroad1->get_top_left_corner();
    auto cr1_br_corner = crossroad1->get_bott_right_corner();
    auto cr2_tl_corner = crossroad2->get_top_left_corner();
    auto cr2_br_corner = crossroad2->get_bott_right_corner();
    bool horizontal = cr1_tl_corner.second == cr2_tl_corner.second;

    std::pair<double, double> top_left_corner;
    std::pair<double, double> bott_right_corner;

    if(horizontal) {
        top_left_corner = std::make_pair(std::min(cr1_br_corner.first, cr2_br_corner.first) + VisConsts::get().road_outline_thickness,
                                         std::min(cr1_tl_corner.second, cr2_tl_corner.second));
        bott_right_corner = std::make_pair(std::max(cr1_tl_corner.first, cr2_tl_corner.first) - VisConsts::get().road_outline_thickness,
                                           std::max(cr1_br_corner.second, cr2_br_corner.second));
    }
    else {
        top_left_corner = std::make_pair(std::min(cr1_tl_corner.first, cr2_tl_corner.first),
                                         std::min(cr1_br_corner.second, cr2_br_corner.second) + VisConsts::get().road_outline_thickness);
        bott_right_corner = std::make_pair(std::max(cr1_br_corner.first, cr2_br_corner.first),
                                           std::max(cr1_tl_corner.second, cr2_tl_corner.second) - VisConsts::get().road_outline_thickness);
    }

    sprite_asphalt.setPosition(top_left_corner.first, top_left_corner.second);
    sprite_asphalt.setSize(sf::Vector2f(bott_right_corner.first - top_left_corner.first,
                                        bott_right_corner.second - top_left_corner.second));
    sprite_asphalt.setOutlineThickness(VisConsts::get().road_outline_thickness);
    sprite_asphalt.setFillColor(VisConsts::get().asphalt_col);
    sprite_asphalt.setOutlineColor(VisConsts::get().road_outline_col);

    sprite_asphalt.setScale(VisConsts::get().scale, VisConsts::get().scale);
    sprite_asphalt.setPosition(sprite_asphalt.getPosition().x * VisConsts::get().scale,
                               sprite_asphalt.getPosition().y * VisConsts::get().scale);
}

void RoadVisual::set_sprite_solid_line() {
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
        sprite_solid_line.setPosition(x_left, mid - VisConsts::get().marking_thickness / 2);
        sprite_solid_line.setSize(sf::Vector2f((x_right - x_left), VisConsts::get().marking_thickness));
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
        sprite_solid_line.setPosition(mid - VisConsts::get().marking_thickness / 2, y_top);
        sprite_solid_line.setSize(sf::Vector2f(VisConsts::get().marking_thickness, (y_bott - y_top)));
    }

    sprite_solid_line.setPosition(sprite_solid_line.getPosition().x * VisConsts::get().scale,
                                  sprite_solid_line.getPosition().y * VisConsts::get().scale);
    sprite_solid_line.setScale(VisConsts::get().scale, VisConsts::get().scale);
    sprite_solid_line.setFillColor(VisConsts::get().marking_col);
}

void RoadVisual::set_sprites_dashed_lines() {
    Crossroad *beg_crossroad = road->get_beg_crossroad();
    Crossroad *end_crossroad = road->get_end_crossroad();
    bool horizontal = (beg_crossroad->get_top_left_corner().second ==
                       end_crossroad->get_top_left_corner().second);

    if(horizontal) {
        int road_width = beg_crossroad->get_bott_right_corner().second - beg_crossroad->get_top_left_corner().second;
        unsigned long forward_lanes_num = road->get_forward_lanes().size();
        unsigned long backward_lanes_num = road->get_backward_lanes().size();
        double step = road_width / (static_cast<double>(forward_lanes_num) + backward_lanes_num);
        if(beg_crossroad->get_top_left_corner().first < end_crossroad->get_top_left_corner().first) {
            double y = beg_crossroad->get_top_left_corner().second + step - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < forward_lanes_num; i++, y += step)
                dashed_line_ys.push_back(y);
            y = beg_crossroad->get_top_left_corner().second + step * (forward_lanes_num + 1) - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < backward_lanes_num; i++, y += step)
                dashed_line_ys.push_back(y);

            for(double x = beg_crossroad->get_bott_right_corner().first + VisConsts::get().dash_padd / 2;
                    x + VisConsts::get().dash_len < end_crossroad->get_top_left_corner().first;
                    x += VisConsts::get().dash_len + VisConsts::get().dash_padd)
                dashed_line_xs.push_back(x);
        }
        else {
            double y = beg_crossroad->get_top_left_corner().second + step - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < backward_lanes_num; i++, y += step)
                dashed_line_ys.push_back(y);
            y = beg_crossroad->get_top_left_corner().second + step * (backward_lanes_num + 1) - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < forward_lanes_num; i++, y += step)
                dashed_line_ys.push_back(y);

            for(double x = end_crossroad->get_bott_right_corner().first + VisConsts::get().dash_padd / 2;
                x + VisConsts::get().dash_len < beg_crossroad->get_top_left_corner().first;
                x += VisConsts::get().dash_len + VisConsts::get().dash_padd)
                dashed_line_xs.push_back(x);
        }

        sprite_dashed_line.setSize(sf::Vector2f(VisConsts::get().dash_len, VisConsts::get().dash_thick));
    }
    else {
        int road_width = beg_crossroad->get_bott_right_corner().first - beg_crossroad->get_top_left_corner().first;
        unsigned long forward_lanes_num = road->get_forward_lanes().size();
        unsigned long backward_lanes_num = road->get_backward_lanes().size();
        double step = road_width / (static_cast<double>(forward_lanes_num) + backward_lanes_num);
        if(beg_crossroad->get_top_left_corner().second < end_crossroad->get_top_left_corner().second) {
            double x = beg_crossroad->get_top_left_corner().first + step - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < forward_lanes_num; i++, x += step)
                dashed_line_xs.push_back(x);
            x = beg_crossroad->get_top_left_corner().first + step * (forward_lanes_num + 1) - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < backward_lanes_num; i++, x += step)
                dashed_line_xs.push_back(x);

            for(double y = beg_crossroad->get_bott_right_corner().second + VisConsts::get().dash_padd / 2;
                y + VisConsts::get().dash_len < end_crossroad->get_top_left_corner().second;
                y += VisConsts::get().dash_len + VisConsts::get().dash_padd)
                dashed_line_ys.push_back(y);
        }
        else {
            double x = beg_crossroad->get_top_left_corner().first + step - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < backward_lanes_num; i++, x += step)
                dashed_line_xs.push_back(x);
            x = beg_crossroad->get_top_left_corner().first + step * (backward_lanes_num + 1) - VisConsts::get().dash_thick / 2;
            for(int i = 1; i < forward_lanes_num; i++, x += step)
                dashed_line_xs.push_back(x);

            for(double y = end_crossroad->get_bott_right_corner().second + VisConsts::get().dash_padd / 2;
                y + VisConsts::get().dash_len < beg_crossroad->get_top_left_corner().second;
                y += VisConsts::get().dash_len + VisConsts::get().dash_padd)
                dashed_line_ys.push_back(y);
        }

        sprite_dashed_line.setSize(sf::Vector2f(VisConsts::get().dash_thick, VisConsts::get().dash_len));
    }

    for(double &x : dashed_line_xs)
        x *= VisConsts::get().scale;
    for(double &y : dashed_line_ys)
        y *= VisConsts::get().scale;
    sprite_dashed_line.setScale(sf::Vector2f(VisConsts::get().scale, VisConsts::get().scale));
    sprite_dashed_line.setFillColor(VisConsts::get().marking_col);
}
