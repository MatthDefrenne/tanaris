-- 
-- Kurmokk
DELETE FROM `creature` WHERE `guid` BETWEEN 134210 AND 134219;
DELETE FROM `creature_addon` WHERE `guid` BETWEEN 134210 AND 134219;
DELETE FROM `pool_creature` WHERE `pool_entry` = 1021;
DELETE FROM `pool_template` WHERE `entry` = 1021;
UPDATE `creature` SET `modelid` = 0, `position_x` = -13769.472, `position_y` = -210.8100, `position_z` = 28.15880, `orientation` = 1.6824140, `MovementType` = 2 WHERE `guid` = 49126;

DELETE FROM `creature_addon` WHERE `guid` IN (49126);
INSERT INTO `creature_addon` (`guid`, `path_id`, `bytes1`, `bytes2`, `auras`) VALUES  
(49126, 491260, 0, 1, '');

DELETE FROM `waypoint_data` WHERE `id`=491260;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_type`, `action_chance`, `wpguid`) VALUES
(491260, 1, -13771.36, -194.1479, 23.58299, 0, 0, 100, 0),
(491260, 2, -13800.65, -171.2549, 16.75194, 0, 0, 100, 0),
(491260, 3, -13825.32, -138.9485, 17.06193, 0, 0, 100, 0),
(491260, 4, -13839.20, -104.7389, 15.74479, 0, 0, 100, 0),
(491260, 5, -13854.54, -89.10059, 16.51101, 0, 0, 100, 0),
(491260, 6, -13880.08, -68.98720, 22.91978, 0, 0, 100, 0),
(491260, 7, -13884.61, -54.92849, 27.63699, 0, 0, 100, 0),
(491260, 8, -13903.91, -29.40885, 29.51131, 0, 0, 100, 0),
(491260, 9, -13907.90, -7.800998, 27.44344, 0, 0, 100, 0),
(491260, 10, -13917.54, 25.832030, 15.02404, 0, 0, 100, 0),
(491260, 11, -13918.52, 50.220270, 15.45375, 0, 0, 100, 0),
(491260, 12, -13935.58, 86.903320, 15.89105, 0, 0, 100, 0),
(491260, 13, -13958.01, 96.246320, 15.29974, 0, 0, 100, 0),
(491260, 14, -13977.52, 107.88300, 13.94238, 0, 0, 100, 0),
(491260, 15, -13996.92, 126.20390, 14.47534, 0, 0, 100, 0),
(491260, 16, -14008.00, 152.99420, 13.52247, 0, 0, 100, 0),
(491260, 17, -14009.72, 182.66020, 13.35314, 0, 0, 100, 0),
(491260, 18, -14022.42, 197.13040, 13.20641, 0, 0, 100, 0),
(491260, 19, -14057.04, 213.87030, 13.23114, 0, 0, 100, 0),
(491260, 20, -14022.42, 197.13040, 13.20641, 0, 0, 100, 0),
(491260, 21, -14009.72, 182.66020, 13.35314, 0, 0, 100, 0),
(491260, 22, -14008.00, 152.99420, 13.52247, 0, 0, 100, 0),
(491260, 23, -13996.92, 126.20390, 14.47534, 0, 0, 100, 0),
(491260, 24, -13977.52, 107.88300, 13.94238, 0, 0, 100, 0),
(491260, 25, -13958.01, 96.246320, 15.29974, 0, 0, 100, 0),
(491260, 26, -13935.58, 86.903320, 15.89105, 0, 0, 100, 0),
(491260, 27, -13918.52, 50.220270, 15.45375, 0, 0, 100, 0),
(491260, 28, -13917.63, 26.220700, 14.77404, 0, 0, 100, 0),
(491260, 29, -13907.90, -7.800998, 27.44344, 0, 0, 100, 0),
(491260, 30, -13903.91, -29.40885, 29.51131, 0, 0, 100, 0),
(491260, 31, -13884.61, -54.92849, 27.63699, 0, 0, 100, 0),
(491260, 32, -13880.08, -68.98720, 22.91978, 0, 0, 100, 0),
(491260, 33, -13854.54, -89.10059, 16.51101, 0, 0, 100, 0),
(491260, 34, -13839.20, -104.7389, 15.74479, 0, 0, 100, 0),
(491260, 35, -13825.32, -138.9485, 17.06193, 0, 0, 100, 0),
(491260, 36, -13800.65, -171.2549, 16.75194, 0, 0, 100, 0),
(491260, 37, -13771.36, -194.1479, 23.58299, 0, 0, 100, 0),
(491260, 38, -13768.64, -210.9160, 28.39240, 0, 0, 100, 0);
