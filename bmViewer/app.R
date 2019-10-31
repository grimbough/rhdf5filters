#
# This is a Shiny web application. You can run the application by clicking
# the 'Run App' button above.
#
# Find out more about building applications with Shiny here:
#
#    http://shiny.rstudio.com/
#

library(shiny)
library(dplyr)
library(ggplot2)
library(ggpubr)
library(RColorBrewer)
library(tidyr)
library(gridExtra)
library(grid)


bm_all <- readRDS("/g/huber/users/msmith/BioconductorPkgs/hdf5Filters/vignettes/bm_all.rds")

# Define UI for application that draws a histogram
ui <- fluidPage(

    # Application title
    titlePanel("Old Faithful Geyser Data"),

    # Sidebar with a slider input for number of bins 
    sidebarLayout(
        sidebarPanel(
            radioButtons("chunk_dims",
                         "Chunk Dimensions",
                         choices = unique(bm_all$chunk_dims)
                         ),
            radioButtons("shuffle",
                         "Shuffle",
                         choices = c(TRUE, FALSE)
            ),
            # radioButtons("baseline",
            #              "Baseline",
            #              choices = list("Absolute values" = TRUE,
            #                             "GZIP default" = FALSE)
            #              ),
            radioButtons("order",
                         "Ordering",
                         choices = list("Median" = 1, "Filter" = 2))
            ,
            
            checkboxGroupInput("filters",
                        "Filters",
                        choices = unique(bm_all$filter),
                        selected = unique(bm_all$filter)
                        ),
            width = 2
        ),

        # Show a plot of the generated distribution
        mainPanel(
            fluidRow(
                column(4,
                    plotOutput("distPlot", height = "500px"),
                ),
                column(4,
                    plotOutput("distPlot2", height = "500px")
                    ),
                column(4,
                    plotOutput("distPlot3", height = "500px")
                    ),
            ),
            fluidRow(
                column(12,
                     plotOutput("legend", height = "50px")
                     ),
            ),
           width = 10
        )
    )
)

# Define server logic required to draw a histogram
server <- function(input, output) {
    
    tmp <- reactive({
        tab <- bm_all %>%
            filter(filter %in% input$filters) %>%
        filter(shuffle == input$shuffle) %>%
        filter(chunk_dims == input$chunk_dims) %>%
        mutate(ID = paste(filter, level, shuffle, sep = "-"))
        
        # if(input$baseline) {
        #      default <- bm_all %>%
        #         filter(shuffle == input$shuffle) %>%
        #         filter(chunk_dims == input$chunk_dims) %>%
        #         filter(filter == "GZIP", level == 6) %>%
        #         summarize(mean_write_time = mean(write_time),
        #                   mean_read_time = mean(read_time),
        #                   file_size = mean(file_size))
        #      
        #      tab <- tab %>% 
        #          mutate(read_time = read_time / default$mean_read_time,
        #                 write_time = write_time / default$mean_read_time,
        #                 file_size = file_size / default$file_size)
        # }
        tab
    })
    
    plot_start <- reactive({
        
        if(input$order == 1) {
            fun <- median
        } else if (input$order == 2) {
            fun = function(x) { x }
        }
        
        tmp() %>%
            ggplot(aes(x = if(input$order == 1) {
                reorder(ID, read_time, FUN = fun)
                } else {
                    ID
                })) +
            scale_color_manual(values = c(brewer.pal(8, "Set2"), "grey30"), 
                               aesthetics = c("color", "fill")) +
            theme(legend.position = "none") 
    })
    
    p3 <- reactive({
        plot_start() +
            geom_bar(aes(y = file_size / 10e6, fill = filter), stat = "identity") +
            theme(legend.position = "bottom") 
    })

    output$distPlot <- renderPlot({

        p1 <- plot_start() +
            geom_boxplot(aes(y = read_time, fill = filter), outlier.shape = NA, alpha = 0.3) +
            geom_jitter(aes(y = read_time, color = filter)) +
            coord_flip() +
            theme_minimal() + 
            theme(legend.position = "none") + 
            ylab("Read Time (sec)") +
            xlab("Compression Level") +
            scale_x_discrete(labels = function(x) { stringr::str_match(x, "-([0-9])-")[,2] })
        p1
    })
    
    output$distPlot2 <- renderPlot({    
        
        p2 <- plot_start() +
            geom_boxplot(aes(y = write_time, fill = filter), outlier.shape = NA, alpha = 0.3) +
            geom_jitter(aes(y = write_time, color = filter)) +
            coord_flip() +
            theme_minimal() + 
            theme(legend.position = "none") +
            ylab("Write Time (sec)") +
            theme(axis.text.y = element_blank(), 
                  axis.ticks.y = element_blank(),
                  axis.title.y = element_blank())
        p2
    })
    
    output$distPlot3 <- renderPlot({
        
        p3 <- p3() +
            coord_flip() +
            theme_minimal() +
            theme(legend.position = "none") +
            theme(axis.text.y = element_blank(), 
                  axis.ticks.y = element_blank(),
                  axis.title.y = element_blank()) +
            ylab("File Size (MB)")
        p3
    })
    
    output$legend <- renderPlot({
        legend <- p3() %>% 
            ggpubr::get_legend() %>% 
            as_ggplot()
        legend
    })
    
}

# Run the application 
shinyApp(ui = ui, server = server)
