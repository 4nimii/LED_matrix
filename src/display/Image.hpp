
class Image {

    private:

        uint8_t[] pixels;
        int size_x;
        int size_y;

    public:

        bool setPixelAt(int x, int y, uint8_t color);
        bool clear();

}
