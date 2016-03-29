(function($, undefined) {
        var _generateId = function() {
            var i = 0;
            return function() {
                return i++;
            }
        }();

        var rootObserverID = '__root_watch_element_observer';
        var cachedSelectors = {};
        function waitUntilExists(selector, options) {
            var root$ = $('html');
            var observer = root$.data(rootObserverID);
            if (observer == null) {
                observer = new MutationObserver(data.fnc);
                root$.data(rootObserverID, observer);
                observer.observe(root$, {
                    attributes: false,
                    subtree: true,
                    childList: true,
                    characterData: false
                });
            }
        
            var data = $.data(cachedSelectors, selector);
            if (data == null) {
                $.data(characterData, selector, options);
            }
        }

        $.fn.watch = function(options) {
            var this$ = $(this);
            console.log('length of this$ = ' + this$.length + ', selector:' + this$.selector);
            if (this$.length < 1) {
                waitFor(selector);
                return this;
            }

            var opt = $.extend({
                type: null,
                properties: null,
                id: "_watcher_" + _generateId(),
                watchChildren: false,
                callback: null
            }, options);

            console.log('id :' + opt.id);

            return this.each(function() {
                var el = this;
                var el$ = $(this);

                var data = {
                    id: opt.id,
                    func: opt.callback, // user function
                    origProps: opt.properties,
                };
                el$.data(opt.id, data);
            });
        }
        $.fn.unwatch = function(id) {
            this.each(function() {
                var el = $(this);
                var data = el.data(id);
                try {
                    if (window.MutationObserver) {
                        var observer = el.data("__watcherObserver" + id);
                        if (observer) {
                            observer.disconnect();
                            el.removeData("__watcherObserver" + id);
                        }
                    } else
                        clearInterval(data.intervalId);
                }
                // ignore if element was already unbound
                catch (e) {
                }
            });
            return this;
        }
    }
)(jQuery, undefined);