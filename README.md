# raymation
A small library that adds XML support for animations (much more in the future hopefully!).

# Example usage
```cpp
TextureXML anim;
bool run = true;

anim.SetState("testOne");
anim.SetFrame(0);
anim.SetFPS(24);

LoadXML("path/to/file/file.xml", anim);

while (run) {
    anim.PlayAnimation(0.0f, true);

    if (anim.IsAnimationFinished()) {
        run = false;
    }

    anim.UpdateTexture();
}
```