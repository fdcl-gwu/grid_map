/*
 * GridMapRosConverter.hpp
 *
 *  Created on: Jul 14, 2014
 *      Author: Péter Fankhauser
 *	 Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

#include "grid_map_core/TypeDefs.hpp"
#include <grid_map_core/GridMap.hpp>
#include <grid_map_msgs/GridMap.h>

// STL
#include <vector>
#include <unordered_map>

// Eigen
#include <Eigen/Core>

// ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/GridCells.h>

namespace grid_map {

/*!
 * ROS interface for the Grid Map library.
 */
class GridMapRosConverter
{
 public:
  /*!
   * Default constructor.
   */
  GridMapRosConverter();

  /*!
   * Destructor.
   */
  virtual ~GridMapRosConverter();

  /*!
   * Converts a ROS grid map message to a grid map object.
   * @param[in] message the grid map message.
   * @param[out] gridMap the grid map object to be initialized.
   * @return true if successful, false otherwise.
   */
  static bool fromMessage(const grid_map_msgs::GridMap& message, grid_map::GridMap& gridMap);

  /*!
   * Converts all layers of a grid map object to a ROS grid map message.
   * @param[in] gridMap the grid map object.
   * @param[out] message the grid map message to be populated.
   */
  static void toMessage(const grid_map::GridMap& gridMap, grid_map_msgs::GridMap& message);

  /*!
   * Converts requested layers of a grid map object to a ROS grid map message.
   * @param[in] gridMap the grid map object.
   * @param[in] layers the layers to be added to the message.
   * @param[out] message the grid map message to be populated.
   */
  static void toMessage(const grid_map::GridMap& gridMap, const std::vector<std::string>& layers,
                        grid_map_msgs::GridMap& message);

  /*!
   * Converts a grid map object to a ROS PointCloud2 message. Set the layer to be transformed
   * as the points of the point cloud with `pointLayer`, all other types will be added as
   * additional fields.
   * @param[in] gridMap the grid map object.
   * @param[in] pointLayer the type that is transformed to points.
   * @param[out] pointCloud the message to be populated.
   */
  static void toPointCloud(const grid_map::GridMap& gridMap, const std::string& pointLayer,
                           sensor_msgs::PointCloud2& pointCloud);

  /*!
   * Converts a grid map object to a ROS PointCloud2 message. Set the layer to be transformed
   * as the points of the point cloud with `pointLayer` and all other types to be added as
   * additional layers with `layersToAdd`.
   * @param[in] gridMap the grid map object.
   * @param[in] layers the layers that should be added as fields to the point cloud. Must include the pointLayer.
   * @param[in] pointLayer the layer that is transformed to points.
   * @param[out] pointCloud the message to be populated.
   */
  static void toPointCloud(const grid_map::GridMap& gridMap, const std::vector<std::string>& layers,
                           const std::string& pointLayer, sensor_msgs::PointCloud2& pointCloud);

  /*!
   * Converts a grid map object to a ROS OccupancyGrid message. Set the layer to be transformed
   * as the cell data of the occupancy grid with `layer`, all other layers will be neglected.
   * @param[in] gridMap the grid map object.
   * @param[in] layer the layer that is transformed to the occupancy cell data.
   * @param[in] dataMin the minimum value of the grid map data (used to normalize the cell data in [min, max]).
   * @param[in] dataMax the maximum value of the grid map data (used to normalize the cell data in [min, max]).
   * @param[out] occupancyGrid the message to be populated.
   */
  static void toOccupancyGrid(const grid_map::GridMap& gridMap, const std::string& layer,
                              float dataMin, float dataMax, nav_msgs::OccupancyGrid& occupancyGrid);

  static void toGridCells(const grid_map::GridMap& gridMap, const std::string& layer,
                          float lowerThreshold, float upperThreshold,
                          nav_msgs::GridCells& gridCells);
};

} /* namespace */
