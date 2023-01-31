#include <list>
#include <viewer/SpriteCutter.hpp>
#include <viewer/Utils.hpp>
#include <profiler/Profiler.hpp>

#include <robot2D/Util/Logger.hpp>
#include <unordered_set>
#include <deque>

namespace viewer {
    std::vector<std::vector<SpriteCutter::colorPoint>>
    SpriteCutter::packColorMap(const robot2D::UIntRect& clipRegion, robot2D::Image& image,
                               robot2D::vec2f worldPosition) {
        PROFILE_FUNCTION();
        auto* pixelBuffer = image.getBuffer();
        std::vector<std::vector<colorPoint>> colorPoints;

        auto size = image.getSize();
        robot2D::vec2i localPosition = {clipRegion.lx - worldPosition.x, clipRegion.ly - worldPosition.y};

        int channelsNum = 4;
        for(int i = 0; i < clipRegion.height; ++i) {
            std::vector<colorPoint> line{clipRegion.width};
            int colorIndex = 4;
            int pixelBufferIndex = (localPosition.y + i) * channelsNum * size.x +
                                   (localPosition.x - 1) * channelsNum;
            for(int j = 0; j < clipRegion.width; ++j) {
                pixelBufferIndex += colorIndex;
                robot2D::Color c = robot2D::Color{pixelBuffer[pixelBufferIndex], pixelBuffer[pixelBufferIndex + 1],
                                                  pixelBuffer[pixelBufferIndex + 2], pixelBuffer[ pixelBufferIndex + 3]};
                auto pos = robot2D::vec2i{localPosition.x + j, localPosition.y + i};
                line[j] = {
                        c,
                        pos
                };
            }
            colorPoints.push_back(line);
        }

        return colorPoints;
    }


    template<typename T, typename Predicate>
    std::vector<T> filter(const std::vector<T>& vector, Predicate&& pred) {
        std::vector<T> filtered;
        for(const auto& i: vector) {
            if(pred(i)) {
                filtered.template emplace_back(i);
            }
        }
        return filtered;
    }

    std::vector<robot2D::vec2i> SpriteCutter::getNeighbors(robot2D::vec2i point, robot2D::Image& image) {
        std::vector<robot2D::vec2i> res;
        auto imageWidth = image.getSize().x;
        auto imageHeight = image.getSize().y;
        using Point = robot2D::vec2i;
        // Left neighbor
        if (point.x > 0)
            res.emplace_back(Point(point.x - 1, point.y));

        // Right neighbor
        if (point.x < imageWidth)
            res.emplace_back(Point(point.x + 1, point.y));

        // Top neighbor
        if (point.y > 0)
            res.emplace_back(Point(point.x, point.y - 1));

        // Bottom neighbor
        if (point.y < imageHeight)
            res.emplace_back(Point(point.x, point.y + 1));

        // Top-left neighbor
        if (point.x > 0 && point.y > 0)
            res.emplace_back(Point(point.x - 1, point.y - 1));

        // Top-right neighbor
        if (point.x < imageWidth && point.y > 0)
            res.emplace_back(Point(point.x + 1, point.y - 1));

        // Bottom-left neighbor
        if (point.x > 0 && point.y < imageHeight - 1)
            res.emplace_back(Point(point.x - 1, point.y + 1));

        // Bottom-right neighbor
        if (point.x < imageWidth && point.y < imageHeight)
            res.emplace_back(Point(point.x + 1, point.y + 1));
        return res;
    }

    robot2D::IntRect SpriteCutter::splitPoints(std::set<robot2D::vec2i>& points) {
        if(points.empty())
            return {};

        auto minPoint = *points.begin();
        auto maxPoint = *points.rbegin();

        return  {
            minPoint.x,
            minPoint.y,
            maxPoint.x - minPoint.x + 1,
            maxPoint.y - minPoint.y + 1,
        };
    }

    robot2D::Color SpriteCutter::getColor(robot2D::Image& image, robot2D::vec2i position) {
        unsigned int pixelBufferIndex = (position.y) * 4 * image.getSize().x + (position.x - 1) * 4;
        auto* buffer = image.getBuffer();
        return {buffer[pixelBufferIndex], buffer[pixelBufferIndex + 1], buffer[pixelBufferIndex + 2],
                buffer[pixelBufferIndex + 3]};
    }

    robot2D::IntRect SpriteCutter::findBoundingBox(robot2D::Image& image, robot2D::vec2i point) {
        //PROFILE_FUNCTION();
        std::vector<robot2D::vec2i> unvisited;
        std::set<robot2D::vec2i> visited;
        std::vector<robot2D::vec2i> neighbors = getNeighbors(point, image);

        static const auto isTransparent = [](const robot2D::Color& color) -> bool {
            return color.alpha > 0;
        };

        for(auto& neighbor: neighbors) {
            auto c = getColor(image, neighbor);
            if(isTransparent(c)) {
                unvisited.emplace_back(neighbor);
            }
        }

        while(!unvisited.empty()) {
            auto curPoint = unvisited.back();
            unvisited.pop_back();
            if(isTransparent(getColor(image, curPoint))) {
                for(auto neighbor: getNeighbors(curPoint, image)) {
                    auto found = std::find(unvisited.begin(), unvisited.end(), neighbor);
                    if(visited.find(neighbor) == visited.end() && found == unvisited.end()
                       && isTransparent(getColor(image, neighbor))) {
                        unvisited.push_back(neighbor);
                    }
                }

                visited.insert(curPoint);
            }
        }

        if(visited.empty())
            return {};

        auto minPoint = *visited.begin();
        auto maxPoint = *visited.rbegin();

        return  {
                minPoint.x,
                minPoint.y,
                maxPoint.x - minPoint.x + 1,
                maxPoint.y - minPoint.y + 1,
        };
    }

    void SpriteCutter::eraseSprite(robot2D::Image& image, robot2D::IntRect rect) {
        //PROFILE_FUNCTION();
        auto* buffer = image.getBuffer();
        constexpr static int channelsNum = 4;
        auto size = image.getSize();
        int pixelBufferIndex = 0;

        for(int i = 0; i < rect.height; ++i) {
            pixelBufferIndex = (rect.ly + i) * channelsNum * size.x +
                                   (rect.lx - 1) * channelsNum;
            for(int j = 0; j < rect.width; ++j) {
                buffer[pixelBufferIndex + 3] = 0;
                pixelBufferIndex += 4;
            }
        }

    }

    std::vector<robot2D::IntRect> SpriteCutter::filterInsideFrames(std::vector<robot2D::IntRect> frames) {
        PROFILE_FUNCTION();
        if(frames.size() <= 1)
            return frames;

        std::sort(frames.begin(), frames.end(), [](const robot2D::IntRect& l, const robot2D::IntRect& r){
            return l.area() < r.area();
        });


        int sz = static_cast<int>(frames.size());
        std::vector<robot2D::IntRect> filteredFrames;
        filteredFrames.reserve(sz);

        int i = 0;
        int j;
        static auto empty = robot2D::IntRect {};

        for(; i < sz; ++i) {
            for(j = sz - 1; j > 0; --j) {
                if(frames[i] == empty || frames[j] == empty)
                    continue;
                if(frames[i].contains(frames[j])) {
                    filteredFrames.emplace_back(frames[i]);
                    frames[j] = {};
                }
                else if(frames[j].contains(frames[i])) {
                    filteredFrames.emplace_back(frames[j]);
                    frames[i] = {};
                }
            }
        }

        filteredFrames.shrink_to_fit();
        return filteredFrames;
    }

    robot2D::IntRect unionFrame(const robot2D::IntRect& frame, const robot2D::IntRect& copyFrame) {
        robot2D::IntRect unionFrame;
        unionFrame.lx = std::min(frame.lx, copyFrame.lx);
        unionFrame.ly = std::min(frame.ly, copyFrame.ly);
        robot2D::vec2i maxPoint = {
                std::max(frame.lx + frame.width, copyFrame.lx + copyFrame.width),
                std::max(frame.ly + frame.height, copyFrame.ly + copyFrame.height)
        };
        unionFrame.width = maxPoint.x - unionFrame.lx;
        unionFrame.height = maxPoint.y - unionFrame.ly;
        return unionFrame;
    }

    struct HashFunction1 {
        size_t operator()(const robot2D::IntRect& rect) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + std::hash<int>()( rect.lx );
            res = res * 31 + std::hash<int>()( rect.ly );
            res = res * 31 + std::hash<int>()( rect.width );
            res = res * 31 + std::hash<int>()( rect.height );
            return res;
        }
    };

    std::pair<std::vector<robot2D::IntRect>, bool>
    SpriteCutter::mergeOverlappingFrames(std::vector<robot2D::IntRect> frames) {
        PROFILE_FUNCTION();
        if(frames.size() <= 1)
            return {frames, false};

        int sz = static_cast<int>(frames.size());
        std::vector<robot2D::IntRect> mergedFrames;
        mergedFrames.reserve(sz);

        static auto empty = robot2D::IntRect {};
        int intersectsCount = 0;
        bool wasMerge = false;
        {
            PROFILE_SCOPE("Actual Merging");
            int i = 0;
            int j;
            for (; i < sz; ++i) {
                for (j = sz - 1; j > 0; --j) {
                    if (frames[i] == frames[j] || frames[j] == empty)
                        continue;
                    if (frames[i].intersects(frames[j])) {
                        auto frame = unionFrame(frames[i], frames[j]);
                        frames[i] = frame;
                        frames[j] = empty;
                        mergedFrames.emplace_back(frame);
                        ++intersectsCount;
                        wasMerge = true;
                    }
                }
                frames.erase(std::remove_if(frames.begin(), frames.end(),
                                            [](const auto& f) {return f == empty;}), frames.end());
                sz = frames.size();
                if(i >= sz)
                    break;
            }
        }
        {
            PROFILE_SCOPE("Sort merged");
            std::unordered_set<robot2D::IntRect, HashFunction1> uniqueFrames;
            for (const auto &frame: frames)
                uniqueFrames.insert(frame);

            mergedFrames.assign(uniqueFrames.begin(), uniqueFrames.end());
            std::sort(mergedFrames.begin(), mergedFrames.end(), [](const robot2D::IntRect &l,
                                                                   const robot2D::IntRect &r) {
                return l.lx < r.lx;
            });

            mergedFrames.shrink_to_fit();
        }
        RB_INFO("Merge Frames Function: intersection unions count = {0}", intersectsCount);
        return {mergedFrames, wasMerge};
    }

    std::vector<robot2D::IntRect>
    SpriteCutter::cutFrames(const robot2D::UIntRect& clipRegion, robot2D::Image& image,
                            robot2D::vec2f worldPosition) {
        PROFILE_FUNCTION();
        std::vector<robot2D::IntRect> frames;
        // do it only once per image for whole
        auto&& colorsPoints = packColorMap(clipRegion, image, worldPosition);

        auto isTransparent = [](const robot2D::Color& color) -> bool {
            return color.alpha > 0;
        };

        robot2D::Image tmpImage;
        {
            //PROFILE_SCOPE("Texture Creation");
            tmpImage.create(image.getSize(), image.getBuffer(), image.getColorFormat());
        }

        {
            PROFILE_SCOPE("Pack Bounding Boxes");
            for(int i = 0; i < colorsPoints.size(); ++i) {
                const auto& line = colorsPoints[i];
                for(int j = 0; j < line.size(); ++j) {
                    if(isTransparent(line[j].first)) {
                        auto&& frame = findBoundingBox(tmpImage, line[j].second);
                        if(frame != robot2D::IntRect{}) {
                            eraseSprite(tmpImage, frame);

                            frame.lx += static_cast<int>(worldPosition.x);
                            frame.ly += static_cast<int>(worldPosition.y);
                            frames.emplace_back(frame);
                        }
                    }
                }
            }
        }


        auto sz = frames.size();
        RB_INFO("ALL FRAMES SIZE = {0}", sz);

        bool needProcess = true;
        {
            PROFILE_SCOPE("Combine Rects");
            while (sz > 1 && needProcess > 0) {
                auto filteredFrames = filterInsideFrames(frames);
                auto mergedFrames = mergeOverlappingFrames(filteredFrames);
                frames = mergedFrames.first;
                needProcess = mergedFrames.second;
            }
        }
        sz = frames.size();
        RB_INFO("ALL FRAMES AFTER SIZE = {0}", sz);
        return frames;
    }

}