-- 
DELETE FROM `creature` WHERE `guid` IN (90490,90518,90781,90805,90871,90873);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`,`spawndist`, `MovementType`) VALUES
(90490, 6071, 1, 1, 1, 0, 0, 1639.91, -3086.87, 88.1959, 5.6608, 300, 0, 0),
(90518, 6071, 1, 1, 1, 0, 0, 1643.2, -3082.28, 88.0567, 5.6608, 300, 0, 0),
(90781, 6071, 1, 1, 1, 0, 0, 1644.94, -3086.83, 88.5227, 5.6608, 300, 0, 2),
(90805, 6071, 1, 1, 1, 0, 0, 1703.05, -3440.01, 144.848, 1.88069, 300, 0, 0),
(90871, 6071, 1, 1, 1, 0, 0, 1699.72, -3441.07, 144.903, 1.88069, 300, 0, 0),
(90873, 6071, 1, 1, 1, 0, 0, 1700.04, -3437.18, 145.013, 1.84535, 300, 0, 2);

DELETE FROM `creature_addon` WHERE `guid` IN (90873,90781);
INSERT INTO `creature_addon` (`guid`, `path_id`, `bytes1`, `bytes2`, `auras`) VALUES  
(90873, 908730, 0, 1, ''),
(90781, 907810, 0, 1, '');

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (90873,90781);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(90873, 90873, 0, 0, 515, 0, 0),
(90873, 90871, 3, 45, 515, 0, 0),
(90873, 90805, 3, 315, 515, 0, 0),
(90781, 90781, 0, 0, 515, 0, 0),
(90781, 90518, 3, 45, 515, 0, 0),
(90781, 90490, 3, 315, 515, 0, 0);

DELETE FROM `waypoint_data` WHERE `id` IN (908730,907810);
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_type`, `action_chance`, `wpguid`) VALUES
(908730, 1, 1698.406, -3431.150, 145.06906, 0, 1, 100, 0),
(908730, 2, 1690.931, -3414.839, 144.86795, 0, 1, 100, 0),
(908730, 3, 1685.137, -3406.095, 144.60960, 0, 1, 100, 0),
(908730, 4, 1676.823, -3394.831, 144.55374, 0, 1, 100, 0),
(908730, 5, 1666.063, -3381.042, 145.24678, 0, 1, 100, 0),
(908730, 6, 1657.185, -3370.217, 145.08261, 0, 1, 100, 0),
(908730, 7, 1642.145, -3350.886, 144.62502, 0, 1, 100, 0),
(908730, 8, 1627.401, -3331.662, 144.39420, 0, 1, 100, 0),
(908730, 9, 1633.344, -3316.238, 144.83813, 0, 1, 100, 0),
(908730, 10, 1639.227, -3296.093, 148.16599, 0, 1, 100, 0),
(908730, 11, 1642.294, -3286.051, 149.50101, 0, 1, 100, 0),
(908730, 12, 1648.342, -3269.644, 148.88351, 0, 1, 100, 0),
(908730, 13, 1654.013, -3256.860, 145.92957, 0, 1, 100, 0),
(908730, 14, 1662.798, -3241.737, 141.11642, 0, 1, 100, 0),
(908730, 15, 1674.169, -3224.093, 134.26839, 0, 1, 100, 0),
(908730, 16, 1687.193, -3206.719, 122.47344, 0, 1, 100, 0),
(908730, 17, 1684.632, -3186.781, 114.02260, 0, 1, 100, 0),
(908730, 18, 1684.616, -3171.820, 104.85282, 0, 1, 100, 0),
(908730, 19, 1698.469, -3157.291, 95.11124, 0, 1, 100, 0),
(908730, 20, 1684.616, -3171.820, 104.85282, 0, 1, 100, 0),
(908730, 21, 1684.632, -3186.781, 114.02260, 0, 1, 100, 0),
(908730, 22, 1687.193, -3206.719, 122.47344, 0, 1, 100, 0),
(908730, 23, 1674.169, -3224.093, 134.26839, 0, 1, 100, 0),
(908730, 24, 1662.798, -3241.737, 141.11642, 0, 1, 100, 0),
(908730, 25, 1654.013, -3256.860, 145.92957, 0, 1, 100, 0),
(908730, 26, 1648.342, -3269.644, 148.88351, 0, 1, 100, 0),
(908730, 27, 1642.294, -3286.051, 149.50101, 0, 1, 100, 0),
(908730, 28, 1639.227, -3296.093, 148.16599, 0, 1, 100, 0),
(908730, 29, 1633.344, -3316.238, 144.83813, 0, 1, 100, 0),
(908730, 30, 1627.401, -3331.662, 144.39420, 0, 1, 100, 0),
(908730, 31, 1642.145, -3350.886, 144.62502, 0, 1, 100, 0),
(908730, 32, 1657.185, -3370.217, 145.08261, 0, 1, 100, 0),
(908730, 33, 1666.063, -3381.042, 145.24678, 0, 1, 100, 0),
(908730, 34, 1676.823, -3394.831, 144.55374, 0, 1, 100, 0),
(908730, 35, 1685.137, -3406.095, 144.60960, 0, 1, 100, 0),
(908730, 36, 1690.931, -3414.839, 144.86795, 0, 1, 100, 0),
(908730, 37, 1698.406, -3431.150, 145.06906, 0, 1, 100, 0),
(907810, 1,  1644.886, -3086.448, 88.46348, 0, 1, 100, 0),
(907810, 2,  1664.393, -3102.120, 88.84255, 0, 1, 100, 0),
(907810, 3,  1680.794, -3115.140, 89.37998, 0, 1, 100, 0),
(907810, 4,  1695.969, -3129.635, 90.66051, 0, 1, 100, 0),
(907810, 5,  1708.420, -3141.912, 92.82675, 0, 1, 100, 0),
(907810, 6,  1728.459, -3159.081, 92.04818, 0, 1, 100, 0),
(907810, 7,  1743.901, -3169.440, 91.24393, 0, 1, 100, 0),
(907810, 8,  1760.458, -3175.052, 90.49347, 0, 1, 100, 0),
(907810, 9,  1784.307, -3179.418, 91.58943, 0, 1, 100, 0),
(907810, 10, 1812.097, -3178.790, 92.27321, 0, 1, 100, 0),
(907810, 11, 1835.781, -3174.461, 93.48922, 0, 1, 100, 0),
(907810, 12, 1862.448, -3165.933, 95.22448, 0, 1, 100, 0),
(907810, 13, 1892.696, -3157.232, 95.93946, 0, 1, 100, 0),
(907810, 14, 1862.448, -3165.933, 95.22448, 0, 1, 100, 0),
(907810, 15, 1835.781, -3174.461, 93.48922, 0, 1, 100, 0),
(907810, 16, 1812.097, -3178.790, 92.27321, 0, 1, 100, 0),
(907810, 17,  1784.307, -3179.418, 91.58943, 0, 1, 100, 0),
(907810, 18,  1760.458, -3175.052, 90.49347, 0, 1, 100, 0),
(907810, 19,  1743.901, -3169.440, 91.24393, 0, 1, 100, 0),
(907810, 20,  1728.459, -3159.081, 92.04818, 0, 1, 100, 0),
(907810, 21,  1708.420, -3141.912, 92.82675, 0, 1, 100, 0),
(907810, 22,  1695.969, -3129.635, 90.66051, 0, 1, 100, 0),
(907810, 23,  1680.794, -3115.140, 89.37998, 0, 1, 100, 0),
(907810, 24,  1664.393, -3102.120, 88.84255, 0, 1, 100, 0),
(907810, 25,  1644.886, -3086.448, 88.46348, 0, 1, 100, 0);
