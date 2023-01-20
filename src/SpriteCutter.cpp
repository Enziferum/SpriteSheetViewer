#include <list>
#include <viewer/SpriteCutter.hpp>

namespace viewer {
    bool contains(const robot2D::IntRect& l, const robot2D::IntRect& r) {
        if(l.lx <= r.lx && l.ly <= r.ly
           && (l.lx + l.width) >= (r.lx + r.width)
           && (l.ly + l.height) >= (r.ly + r.height))
            return true;
        else
            return false;
    }

    template<typename T>
    bool intersectsRect(const robot2D::Rect<T>& l, const robot2D::Rect<T>& other) {
        T minX = std::min(l.lx, static_cast<T>(l.lx + l.width));
        T maxX = std::max(l.lx, static_cast<T>(l.lx + l.width));
        T minY = std::min(l.ly, static_cast<T>(l.ly + l.height));
        T maxY = std::max(l.ly, static_cast<T>(l.ly + l.height));

        T minX2 = std::min(other.lx, static_cast<T>(other.lx + other.width));
        T maxX2 = std::max(other.lx, static_cast<T>(other.lx + other.width));
        T minY2 = std::min(other.ly, static_cast<T>(other.ly + other.height));
        T maxY2 = std::max(other.ly, static_cast<T>(other.ly + other.height));

        T innerLeft = std::max(minX, minX2);
        T innerTop = std::max(minY, minY2);
        T innerRight = std::min(maxX, maxX2);
        T innerBottom = std::min(maxY, maxY2);

        bool result = false;
        if(((innerLeft <= innerRight) && (innerTop <= innerBottom))) {
            //overlap = {innerLeft, innerTop, innerRight - innerLeft, innerBottom - innerTop};
            result = true;
        } else {
            //overlap = {};
            result = false;
        }

        return result;
    }

    std::vector<std::vector<SpriteCutter::colorPoint>>
    SpriteCutter::packColorMap(const robot2D::UIntRect& clipRegion, robot2D::Texture& texture,
                               robot2D::vec2f worldPosition) {

        auto* pixelBuffer = texture.getPixels();
        std::vector<std::vector<colorPoint>> colorPoints;

        auto size = texture.getSize();
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
            res.push_back(Point(point.x - 1, point.y));

        // Right neighbor
        if (point.x < imageWidth)
            res.push_back(Point(point.x + 1, point.y));

        // Top neighbor
        if (point.y > 0)
            res.push_back(Point(point.x, point.y - 1));

        // Bottom neighbor
        if (point.y < imageHeight)
            res.push_back(Point(point.x, point.y + 1));

        // Top-left neighbor
        if (point.x > 0 && point.y > 0)
            res.push_back(Point(point.x - 1, point.y - 1));

        // Top-right neighbor
        if (point.x < imageWidth && point.y > 0)
            res.push_back(Point(point.x + 1, point.y - 1));

        // Bottom-left neighbor
        if (point.x > 0 && point.y < imageHeight - 1)
            res.push_back(Point(point.x - 1, point.y + 1));

        // Bottom-right neighbor
        if (point.x < imageWidth && point.y < imageHeight)
            res.push_back(Point(point.x + 1, point.y + 1));
        return res;
    }


    robot2D::IntRect SpriteCutter::splitPoints(std::set<robot2D::vec2i>& points) {
        if(points.empty())
            return {};

        std::vector<robot2D::vec2i> v_points;
        for(auto& p: points)
            v_points.push_back(p);

        robot2D::vec2i min_xP = v_points[0];
        for(int i = 1; i < v_points.size(); ++i) {
            if(min_xP.x > v_points[i].x)
                min_xP = v_points[i];
        }

        robot2D::vec2i min_yP = v_points[0];
        for(int i = 1; i < v_points.size(); ++i) {
            if(min_yP.y > v_points[i].y)
                min_yP = v_points[i];
        }

        robot2D::vec2i max_xP = v_points[0];
        for(int i = 1; i < v_points.size(); ++i) {
            if(max_xP.x < v_points[i].x)
                max_xP = v_points[i];
        }

        robot2D::vec2i max_yP = v_points[0];
        for(int i = 1; i < v_points.size(); ++i) {
            if(max_yP.y < v_points[i].y)
                max_yP = v_points[i];
        }

        int left = min_xP.x;
        int top = min_yP.y;
        int right = max_xP.x;
        int bottom = max_yP.y;

        robot2D::IntRect rect;
        rect.lx = left;
        rect.ly = top;
        rect.width = right - left + 1;
        rect.height = bottom - top + 1;
        return rect;
    }

    robot2D::Color SpriteCutter::getColor(robot2D::Image& image, robot2D::vec2i position) {
        unsigned int pixelBufferIndex = (position.y) * 4 * image.getSize().x + (position.x - 1) * 4;
        auto* buffer = image.getBuffer();
        return {buffer[pixelBufferIndex], buffer[pixelBufferIndex + 1], buffer[pixelBufferIndex + 2], buffer[pixelBufferIndex + 3]};
    }

    robot2D::IntRect SpriteCutter::findBoundingBox(robot2D::Image& image, robot2D::vec2i point) {
        std::list<robot2D::vec2i> unvisited;
        std::set<robot2D::vec2i> visited;
        std::vector<robot2D::vec2i> neighbors = getNeighbors(point, image);

        auto isTransparent = [](const robot2D::Color& color) -> bool {
            return color.alpha == 255;
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

        return splitPoints(visited);
    }

    void SpriteCutter::eraseSprite(robot2D::Image& image, robot2D::IntRect rect) {
        auto* buffer = image.getBuffer();
        int channelsNum = 4;
        auto size = image.getSize();

        for(int i = 0; i < rect.height; ++i) {
            int pixelBufferIndex = (rect.ly + i) * channelsNum * size.x +
                                   (rect.lx - 1) * channelsNum;
            for(int j = 0; j < rect.width; ++j) {
                buffer[pixelBufferIndex + 3] = 0;
                pixelBufferIndex += 4;
            }
        }

    }

    std::vector<robot2D::IntRect> SpriteCutter::filterInsideFrames(std::vector<robot2D::IntRect> frames) {
        if(frames.size() <= 1)
            return frames;

        std::sort(frames.begin(), frames.end(), [](robot2D::IntRect l, robot2D::IntRect r){
            return (l.width * l.height) < (r.width * r.height);
        });

        auto copyReversed = frames;
        std::reverse(copyReversed.begin(), copyReversed.end());

        std::vector<robot2D::IntRect> filteredFrames;

        for(auto& frame: frames) {
            for(auto& copyFrame: copyReversed) {
                if((frame.width * frame.height) >= (copyFrame.width * copyFrame.height)) {
                    filteredFrames.emplace_back(frame);
                    break;
                }

                if(contains(copyFrame, frame))
                    break;
            }
        }

        return filteredFrames;
    }

    std::pair<std::vector<robot2D::IntRect>, bool> SpriteCutter::mergeOverlappingFrames(std::vector<robot2D::IntRect> frames) {
        if(frames.size() <= 1)
            return {frames, false};

        auto copyReversed = frames;
        std::reverse(copyReversed.begin(), copyReversed.end());

        std::list<robot2D::IntRect> l;
        for(auto& frame: frames)
            l.push_back(frame);

        bool wasMerge = false;
        for(auto& frame: frames) {
            for(auto& copyFrame: copyReversed) {
                if(frame == copyFrame)
                    break;
                if(intersectsRect(frame, copyFrame)) {
                    robot2D::IntRect unionFrame;
                    unionFrame.lx = std::min(frame.lx, copyFrame.lx);
                    unionFrame.ly = std::min(frame.ly, copyFrame.ly);
                    robot2D::vec2i maxPoint = {
                            std::max(frame.lx + frame.width, copyFrame.lx + copyFrame.width),
                            std::max(frame.ly + frame.height, copyFrame.ly + copyFrame.height)
                    };
                    unionFrame.width = maxPoint.x - unionFrame.lx;
                    unionFrame.height = maxPoint.y - unionFrame.ly;

                    l.remove(frame);
                    l.remove(copyFrame);
                    l.push_back(unionFrame);
                    wasMerge = true;
                }
            }
        }
        std::vector<robot2D::IntRect> mergedFrames;
        for(auto& frame: l)
            mergedFrames.emplace_back(frame);
        return {mergedFrames, wasMerge};
    }

    std::vector<robot2D::IntRect>
    SpriteCutter::cutFrames(const robot2D::UIntRect& clipRegion, robot2D::Texture& texture, robot2D::vec2f worldPosition) {

        std::vector<robot2D::IntRect> frames;
        auto&& colorsPoints = packColorMap(clipRegion, texture, worldPosition);

        auto isTransparent = [](const robot2D::Color& color) -> bool {
            return color.alpha == 255;
        };

        robot2D::Image image;
        image.create(texture.getSize(), texture.getPixels(), texture.getColorFormat());

        for(int i = 0; i < colorsPoints.size(); ++i) {
            const auto& line = colorsPoints[i];
            for(int j = 0; j < line.size(); ++j) {
                if(isTransparent(line[j].first)) {

                    auto&& frame = findBoundingBox(image, line[j].second);
                    if(frame != robot2D::IntRect{}) {
                        eraseSprite(image, frame);

                        frame.lx += worldPosition.x;
                        frame.ly += worldPosition.y;
                        frames.emplace_back(frame);
                    }
                }
            }
        }
        auto sz = frames.size();
        bool needProcess = true;
        while(sz > 1 && needProcess) {
            auto filteredFrames = filterInsideFrames(frames);
            auto mergedFrames = mergeOverlappingFrames(filteredFrames);
            frames = mergedFrames.first;
            needProcess = mergedFrames.second;
        }

        return frames;
    }

}