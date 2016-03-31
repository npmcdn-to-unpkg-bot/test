var Task = {
    createNew : function(check, onReady) {
        var task = {};
        task.check = check;
        task.onReady = onReady;
        task.watch = function(selector) {
            if (check()) {
                onReady();
                return;
            }

            $(selector).watch({
                properties: 'prop_innerHTML',
                callback: function() {
                    if (check()) onReady();
                }
            });
        }
        return task;
    }
}