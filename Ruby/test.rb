require 'glfw3'
require 'opengl-core'

# Initialize GLFW 3
Glfw.init

# Create a window
window = Glfw::Window.new(800, 600, "Foobar")

# Set some callbacks
window.set_key_callback do |window, key, code, action, mods|
  window.should_close = true if key == Glfw::KEY_ESCAPE
end

window.set_close_callback do |window|
  window.should_close = true
end

# Make the window's context current
window.make_context_current
loop do
  # And do stuff
  Glfw.wait_events
  GL.glClear(GL::GL_COLOR_BUFFER_BIT | GL::GL_DEPTH_BUFFER_BIT)
  window.swap_buffers
  break if window.should_close?
end

# Explicitly destroy the window when done with it.
window.destroy
